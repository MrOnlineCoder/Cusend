/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_REQUEST_H
#define CSD_REQUEST_H

#include <string>

#include <unordered_map>

namespace csd {
	namespace Methods {
		const std::string Get = "GET";
		const std::string Post = "POST";
		const std::string Put = "PUT";
		const std::string Delete = "DELETE";
	};

	class Request {
	public:
		int m_httpVersion;
		std::string m_method;
		std::string m_url;
		std::string m_ip;

		std::unordered_map<std::string, std::string> m_headers;

		std::string getHeader(std::string name);
	};
}

#endif // !CSD_REQUEST_H
