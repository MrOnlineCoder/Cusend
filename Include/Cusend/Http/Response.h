/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_RESPONSE_H
#define CSD_RESPONSE_H

#include <string>

#include <unordered_map>

#include <Cusend/Core/Memory.h>

namespace csd {
	class Response {
	public:
		Response();
		void setHeader(const std::string& name, const std::string& value);
		void setBody(const std::string& body);
		void setBody(csd::Buffer& body);
		void setStatus(int code);

		void setVersion(int ver);

		void generate(csd::Buffer& target);

		std::size_t computeResponseSize();

		std::size_t getBodySize();

		static std::string makeStatusMessage(int statusCode);
	private:
		int m_version;
		int m_status;
		csd::Buffer m_buffer;
		std::unordered_map<std::string, std::string> m_headers;
	};
}

#endif // !CSD_RESPONSE_H
