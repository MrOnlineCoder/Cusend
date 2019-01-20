/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_ROUTER_H
#define CSD_ROUTER_H

#include <string>
#include <vector>
#include <functional>

#include <Cusend/Http/Request.h>
#include <Cusend/Http/Response.h>

namespace csd {
	typedef std::function<bool(csd::Request&, csd::Response&)> RouteHandler;

	struct Route {
		std::string method;
		std::string url;
		RouteHandler handler;
	};

	class Router {
	public:
		Router();

		void addRoute(csd::Route& route);

		csd::Route* findMatchingRoute(csd::Request& req);
	private:
		std::vector<csd::Route> m_routes;
	};
}

#endif // !CSD_ROUTER_H
