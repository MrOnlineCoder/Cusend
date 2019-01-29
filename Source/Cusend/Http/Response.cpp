/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Http/Response.h>

#include <sstream>

//Sorry for that hardcode!
std::string csd::Response::makeStatusMessage(int statusCode) {
	switch (statusCode) {
	case 200:
		return "OK";
	case 201:
		return "Created";
	case 202:
		return "Accepted";
	case 204:
		return "No Content";
	case 300:
		return "Multiple Choices";
	case 301:
		return "Moved Permanently";
	case 302:
		return "Moved Temporarily";
	case 304:
		return "Not Modified";
	case 400:
		return "Bad Request";
	case 401:
		return "Unauthorized";
	case 403:
		return "Forbidden";
	case 404:
		return "Not Found";
	case 413:
		return "Payload Too Large";
	case 422:
		return "Unprocessable Entity";
	case 429:
		return "Too Many Requests";
	case 500:
		return "Internal Server Error";
	case 501:
		return "Not Implemented";
	case 502:
		return "Bad Gateway";
	default:
		return "Unknown";
	}
}

csd::Response::Response() {
	m_status = 200;
}

void csd::Response::setHeader(const std::string& name, const std::string& value) {
	m_headers.insert(std::make_pair(name, value));
}

void csd::Response::setBody(const std::string& body) {
	csd::freeBuffer(&m_buffer);
	csd::makeEmptyBuffer(&m_buffer, body.size()+1);

	body.copy(m_buffer.data, body.size());

	m_buffer.data[body.size()] = '\0';

	m_buffer.usedSize = body.size();

}

void csd::Response::setBody(csd::Buffer& body) {
	csd::freeBuffer(&m_buffer);
	csd::makeEmptyBuffer(&m_buffer, body.size);

	std::memcpy(m_buffer.data, body.data, body.size);

	m_buffer.usedSize = m_buffer.size;
}

void csd::Response::setStatus(int code) {
	m_status = code;
}

void csd::Response::setVersion(int ver) {
	m_version = ver;
}

void csd::Response::setCookie(const std::string & name, const std::string & value, long age, bool httpOnly) {
	std::stringstream ss;

	ss << name << "=" << value;

	if (age != 0 || httpOnly) {
		ss << "; ";
	}

	if (age != 0) {
		ss << "Max-Age=" << age;
		if (httpOnly) ss << "; ";
	}

	if (httpOnly) {
		ss << "HttpOnly";
	}

	setHeader("Set-Cookie", ss.str());
}

void csd::Response::generate(csd::Buffer& target) {
	csd::freeBuffer(&target);

	setHeader("Content-Length", std::to_string(m_buffer.usedSize));

	std::string response = "";

	std::string verStr = "";

	if (m_version == 0) verStr = "HTTP/1.0";
	if (m_version == 1) verStr = "HTTP/1.1";
	if (m_version == 2) verStr = "HTTP/2.0";

	std::stringstream ss;
	ss << verStr << " " << m_status << " " << makeStatusMessage(m_status) << "\r\n";
	
	std::unordered_map<std::string, std::string>::iterator it;

	for (it = m_headers.begin(); it != m_headers.end(); it++) {
		ss << it->first << ": " << it->second << "\r\n";
	}

	ss << "\r\n";

	for (std::size_t i = 0; i < m_buffer.usedSize; i++) {
		ss << m_buffer.data[i];
	}

	ss << "\0";

	response = ss.str();

	csd::makeEmptyBuffer(&target, response.size()+1);

	for (std::size_t i = 0; i < response.size(); i++) {
		target.data[i] = response[i];
	}

	target.data[response.size()] = '\0';

	target.usedSize = response.size();
}


std::size_t csd::Response::getBodySize() {
	return m_buffer.usedSize;
}
