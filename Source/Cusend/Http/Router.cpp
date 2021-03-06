/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Http/Router.h>

csd::Router::Router(){
	m_routes.reserve(16);
}

void csd::Router::addRoute(csd::Route& route) {
	m_routes.push_back(route);
}

void csd::Router::addMiddleware(csd::MiddlewareHandler& func) {
	m_middlewares.push_back(func);
}

bool csd::Router::processMiddlewares(csd::Request & req, csd::Response & res) {
	for (std::size_t i = 0; i < m_middlewares.size(); i++) {
		MiddlewareHandler& mdlw = m_middlewares[i];

		bool retVal = mdlw(req, res);

		if (!retVal) return false;
	}

	return true;
}

csd::Route* csd::Router::findMatchingRoute(csd::Request& req) {
	for (std::size_t i = 0; i < m_routes.size(); i++) {
		Route& route = m_routes[i];

		if (route.method != req.m_method) continue;
		if (route.url != req.getPath()) continue;

		return &route;
	}

	return NULL;
}
