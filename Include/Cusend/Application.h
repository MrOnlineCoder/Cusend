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
	/**
	* \brief Size for a buffer, which is used to recv() request data into
	*/
	const static int REQUEST_BUFFER_SIZE = 2048;

	/**
	* \brief Main Cusend framework class
	*/
	class Application {
	public:
		/**
		* \brief Default constructor
		*/
		Application();

		/**
		* \brief Default destructor
		*/
		~Application();

		/**
		* \brief Registers a new route for the Application
		* Your application can consist of many routes - basically API endpoints. Route is built of request method, URL (path) and function handler
		* Example: when user tries to access yoursite.com/posts, Cusend will try to give control to registered route "GET /posts"
		* \param method HTTP method for route. Valid values are GET, POST, PUT, DELETE. Use csd::Methods constants as a helper
		* \param uri URI for the route. It must start with a slash (/). Example: /posts, /settings/billing, etc.
		* \param handler Handler function which will be used for the route. It is an std::function, so you can pass both free and member functions
		*/
		void route(const std::string& method, const std::string& uri, RouteHandler handler);

		/**
		* \brief Starts the application on given port
		* Starts listening on given port. This function is blocking, so no code will be executed until it exits
		* \return Returns true if there were no errors. Returns false if there was an error during server setup.
		*/
		bool listen(uint16_t port);

		void stop();
		
		/**
		* \brief Get last Cusend error
		* \return One of csd::Errors constants. csd::Errors:None means there was no error.
		*/
		const csd::Error getError();

		/**
		* \brief Get network error
		* \return Native socket error. Values will differ on different platforms.
		*/
		const int getSocketError();


		static void staticThreadStarter(NetworkClient* client);
		void processClient(NetworkClient* client);

		static csd::Application* instance;
	private:
		bool m_running;
		csd::Error m_error;
		csd::Server m_server;
		csd::RequestParser m_parser;
		csd::Router m_router;
	};
}

#endif // !CSD_APPLICATION_H
