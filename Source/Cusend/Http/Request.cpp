/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Http/Request.h>
#include <Cusend/Core/Common.h>

std::string csd::Request::getHeader(std::string name) {
	std::unordered_map<std::string, std::string>::iterator it = m_headers.find(csd::toUpperCase(name));

	if (it == m_headers.end()) return "";

	return it->second;
}
