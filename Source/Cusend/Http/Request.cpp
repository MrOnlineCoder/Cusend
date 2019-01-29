/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Http/Request.h>
#include <Cusend/Core/Common.h>

std::string csd::Request::getHeader(std::string name) {
	RequestMap::iterator it = m_headers.find(csd::toUpperCase(name));

	if (it == m_headers.end()) return "";

	return it->second;
}

std::string csd::Request::getField(const std::string & key) {
	RequestMap::iterator it = m_fields.find(key);

	if (it == m_fields.end()) return "";

	return it->second;
}

std::string csd::Request::getPath() {
	std::size_t pos = m_url.find_first_of('?');

	return pos == std::string::npos ? m_url : m_url.substr(0, pos);
}


std::string csd::Request::getCookie(const std::string & name) {
	RequestMap::iterator it = m_cookies.find(name);

	if (it == m_cookies.end()) return "";

	return it->second;
}
