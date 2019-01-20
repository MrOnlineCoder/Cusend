/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_APPLICATION_H
#define CSD_APPLICATION_H

#include <cstdint>

#include <Cusend/Core/Error.h>
#include <Cusend/Http/Server.h>
#include <Cusend/Http/Request.h>
#include <Cusend/Http/RequestParser.h>
#include <Cusend/Http/Response.h>
#include <Cusend/Http/Router.h>
#include <Cusend/Http/ResponseFactory.h>

namespace csd {
	const static int REQUEST_BUFFER_SIZE = 1024;

	class Application {
	public:
		Application();
		~Application();

		void route(const std::string& method, const std::string& uri, RouteHandler handler);
		bool listen(uint16_t port);

		void stop();

		const csd::Error getError();
		const int getSocketError();

		static void staticThreadStarter(NetworkClient* client);

		static csd::Application* instance;

		void processClient(NetworkClient* client);
	private:
		bool m_running;
		csd::Error m_error;
		csd::Server m_server;
		csd::RequestParser m_parser;
		csd::Router m_router;
	};
}

#endif // !CSD_APPLICATION_H
