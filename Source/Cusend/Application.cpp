/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Application.h>

#include <Cusend/Platform/Platform.h>
#include <Cusend/Core/Memory.h>


csd::Application* csd::Application::instance = NULL;

csd::Application::Application() {
	m_error = csd::Errors::None;
	m_running = false;

	instance = this;
}

csd::Application::~Application() {
	instance = NULL;
}

void csd::Application::route(const std::string& method, const std::string& uri, RouteHandler handler) {
	csd::Route r;
	r.method = method;
	r.url = uri;
	r.handler = handler;

	m_router.addRoute(r);
}

void csd::Application::use(MiddlewareHandler handler) {
	m_router.addMiddleware(handler);
}

bool csd::Application::listen(uint16_t port) {
	if (!csd::Platform::preInitSockets()) {
		m_error = csd::Errors::PlatformSocketInitFailed;
		return false;
	}

	if (!m_server.createSocket()) {
		m_error = csd::Errors::SocketCreateFailed;
		return false;
	}

	if (!m_server.bind(port)) {
		m_error = csd::Errors::BindSocketFailed;
		return false;
	}

	if (!m_server.listen()) {
		m_error = csd::Errors::ListenSocketFailed;
		return false;
	}

	m_running = true;

	while (m_running) {
		csd::NetworkClient* client = new csd::NetworkClient();
		
		m_server.acceptNextClient(client);

		csd::Platform::startThread(csd::Application::staticThreadStarter, client);
	}

	return true;
}

void csd::Application::stop() {
	m_running = false;
}

const csd::Error csd::Application::getError() {
	return m_error;
}

const int csd::Application::getSocketError() {
	return csd::Platform::getLastSocketError();
}

void csd::Application::staticThreadStarter(NetworkClient* client) {
	Application::instance->processClient(client);
}

void csd::Application::processClient(NetworkClient* client) {
	//Create buffer for reading the request
	csd::Buffer buffer = csd::nullBuffer();
	csd::makeEmptyBuffer(&buffer, REQUEST_BUFFER_SIZE);

	int bytesRead = m_server.receiveIntoBuffer(*client, buffer);

	if (bytesRead <= 0) {
		csd::Platform::shutdownSocket(client->socket);
		csd::Platform::closeSocket(client->socket);
		return;
	}
	
	//Create request and response objects
	csd::Request requestObj;
	csd::Response responseObj;

	//Parse request
	m_parser.clear();
	m_parser.parse(buffer, requestObj);

	//Execute middlewares
	bool shouldExecuteRoute = m_router.processMiddlewares(requestObj, responseObj);

	//Find the route and give control to user code
	if (shouldExecuteRoute) {
		csd::Route* routePtr = m_router.findMatchingRoute(requestObj);

		if (routePtr != NULL) {
			routePtr->handler(requestObj, responseObj);
		}
		else {
			//ExpressJS-style error
			csd::ResponseFactory::text(responseObj, "Cannot " + requestObj.m_method + " " + requestObj.m_url);
		}
	}

	//Generate the response data
	csd::Buffer responseBuffer = csd::nullBuffer();
	responseObj.generate(responseBuffer);

	//Send it over network
	int bytesSent = ::send(client->socket, responseBuffer.data, responseBuffer.size, 0);

	//Cleanup
	csd::freeBuffer(&buffer);
	csd::Platform::shutdownSocket(client->socket);
	csd::Platform::closeSocket(client->socket);
	delete client;
}
