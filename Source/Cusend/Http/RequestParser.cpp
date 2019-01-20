/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Http/RequestParser.h>
#include <Cusend/Core/Common.h>

csd::RequestParser::RequestParser() {
	m_lines.reserve(32);
}

void csd::RequestParser::clear() {
	m_lines.clear();
}

bool csd::RequestParser::parse(csd::Buffer & data, csd::Request & target) {
	//Splitting the whole buffer into std::strings
	std::string line = "";

	for (std::size_t i = 0; i < data.usedSize; i++) {

		if (data.data[i] == '\r') {
			i ++;
			m_lines.push_back(line);
			line = "";
			continue;
		}

		line += data.data[i];
	}

	if (m_lines.size() == 0) {
		return false;
	}

	parseRequestLine(target);
	parseHeaders(target);

	return true;
}

bool csd::RequestParser::parseRequestLine(csd::Request & target) {
	std::string reqLine = m_lines[0];

	std::size_t idx = 0;

	target.m_method = "";
	target.m_httpVersion = -1;
	target.m_url = "";

	//Parse method
	for (; idx < reqLine.size(); idx++) {
		if (reqLine[idx] == ' ') break;

		target.m_method += reqLine[idx];
	}

	idx++;

	//Parse url
	for (; idx < reqLine.size(); idx++) {
		if (reqLine[idx] == ' ') break;

		target.m_url += reqLine[idx];
	}

	idx++;

	std::string httpVerRaw = "";
	for (; idx < reqLine.size(); idx++) {
		httpVerRaw += reqLine[idx];
	}

	if (httpVerRaw.substr(0, 5) != "HTTP/") {
		return false;
	}

	httpVerRaw = httpVerRaw.substr(5);

	if (httpVerRaw == "1.0") target.m_httpVersion = 0;
	if (httpVerRaw == "1.1") target.m_httpVersion = 1;
	if (httpVerRaw == "2.0") target.m_httpVersion = 2;

	return true;
}

bool csd::RequestParser::parseHeaders(csd::Request& target) {
	for (std::size_t idx = 1; idx < m_lines.size(); idx++) {
		if (m_lines[idx] == "\r\n") break;

		std::string line = m_lines[idx];

		std::string name = "";
		std::string value = "";

		bool isNameParsed = false;

		for (std::size_t li = 0; li < line.length(); li++) {
			if (line[li] == ':') {
				isNameParsed = true;
				li++;
				continue;
			}

			if (!isNameParsed) {
				name += line[li];
			} else {
				value += line[li];
			}
		}
		target.m_headers.insert(std::make_pair(csd::toUpperCase(name), value));
	}

	return true;
}
