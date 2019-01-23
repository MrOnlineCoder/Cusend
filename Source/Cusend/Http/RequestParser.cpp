/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Http/RequestParser.h>
#include <Cusend/Core/Common.h>

#include <iostream>

csd::RequestParser::RequestParser() {
	m_lines.reserve(32);
}

void csd::RequestParser::clear() {
	m_lines.clear();
}

bool csd::RequestParser::parse(csd::Buffer & data, csd::Request & target) {
	//Splitting the whole buffer into std::strings
	std::string line = "";

	bool prevNewline = false;

	for (std::size_t i = 0; i < data.usedSize; i++) {

		if (data.data[i] == '\r') {
			i++;
			m_lines.push_back(line);
			line = "";

			if (prevNewline == true) {
				m_lines.push_back("\r\n");
				prevNewline = false;
			}

			prevNewline = true;
			continue;
		}

		line += data.data[i];
		prevNewline = false;
	}

	m_lines.push_back(line);

	if (m_lines.size() == 0) return false;

	if (!parseRequestLine(target)) return false;
	if (!parseHeaders(target)) return false;

	if (target.m_method == csd::Methods::Get) {
		parseGetParams(target);
	} else if (target.m_method == csd::Methods::Post)  {
		parsePostBody(target);
	}

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
		if (m_lines[idx][0] == '\r' && m_lines[idx][1] == '\n') {
			break;
		}

		std::string line = m_lines[idx];

		std::string name = "";
		std::string value = "";

		bool isNameParsed = false;

		for (std::size_t li = 0; li < line.length(); li++) {
			if (line[li] == ':' && !isNameParsed) {
				isNameParsed = true;
				li++;
				continue;
			}

			if (!isNameParsed) {
				name += line[li];
			} else {
				if (value.size() == 0 && line[li] == ' ') continue;

				value += line[li];
			}
		}
		target.m_headers.insert(std::make_pair(csd::toUpperCase(name), value));
	}

	return true;
}

bool csd::RequestParser::parseGetParams(csd::Request & target) {
	std::string query = target.m_url;

	std::size_t qpos = query.find_first_of('?');

	//If there are no GET params to parse, just return
	if (qpos == std::string::npos) {
		return true;
	}

	//Ignore if ? is last character (example.com/test? is a valid URL)
	if (query[query.size() - 1] == '?') {
		return true;
	}

	query = query.substr(qpos+1);
	
	parseFields(target, query);

	return true;
}

bool csd::RequestParser::parsePostBody(csd::Request & target) {
	if (target.getHeader("Content-Type") == "application/x-www-form-urlencoded") {
		parseUrlEncodedBody(target);
		return true;
	}

	//TODO: implement multipart/form-data parsing
	return false;
}

void csd::RequestParser::parseUrlEncodedBody(csd::Request& target) {
	std::size_t idx = 1;

	for (; idx < m_lines.size(); idx++) {
		if (m_lines[idx] == "\r\n") break;
	}

	//At this point idx will point to \r\n line between headers and body
	idx++;

	if (idx < m_lines.size()) {
		parseFields(target, m_lines[idx]);
	}
}

/*
	This can be implemented as a parser with tokenizer
	But currently it works well :D
*/
void csd::RequestParser::parseFields(csd::Request & target, const std::string & str) {
	std::string field;
	std::string value;

	bool isFieldSet = false;

	for (std::size_t i = 0; i < str.size(); i++) {
		char c = str[i];

		if (c == '&') {
			target.m_fields.insert(std::make_pair(field, value));
			field = "";
			value = "";
			isFieldSet = false;
			continue;
		}

		if (c == '=') {
			isFieldSet = true;
			continue;
		}

		if (isFieldSet) {
			value += c;
		} else {
			field += c;
		}
	}

	target.m_fields.insert(std::make_pair(field, value));
}
