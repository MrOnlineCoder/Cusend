/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_REQUESTPARSER_H
#define CSD_REQUESTPARSER_H

#include <Cusend/Core/Memory.h>
#include <Cusend/Http/Request.h>

#include <string>
#include <vector>

namespace csd {
	class RequestParser {
	public:
		RequestParser();

		void clear();

		bool parse(csd::Buffer& data, csd::Request& target);
	private:
		bool parseRequestLine(csd::Request& target);
		bool parseHeaders(csd::Request& target);

		std::vector<std::string> m_lines;
	};
}

#endif // !CSD_REQUESTPARSER_H
