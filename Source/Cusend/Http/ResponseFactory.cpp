/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/
#include <Cusend/Http/ResponseFactory.h>

#include <ctime>
#include <string>

#include <fstream>
#include <iostream>

static std::string getHttpDate() {
	char buf[128];
	time_t now = time(0);
	struct tm tm;
	gmtime_s(&tm, &now);

	//TODO: fix timezones formatting
	strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S GMT", &tm);
	return std::string(buf);
}

static std::string getExtensionFromPath(std::string path) {
	return path.substr(path.find_last_of(".") + 1);
}

//
//Awful code #2
//TODO: create full list as much as possible
//Probably add a parser for http://svn.apache.org/repos/asf/httpd/httpd/trunk/docs/conf/mime.types
//
static std::string getMimeType(std::string extension) {
	//Text files
	if (extension == "html") {
		return "text/html";
	}

	if (extension == "css") {
		return "text/css";
	}

	if (extension == "js") {
		return "text/javascript";
	}

	if (extension == "txt") {
		return "text/plain";
	}

	//Image files
	if (extension == "png") {
		return "image/pnf";
	}

	if (extension == "gif") {
		return "image/gif";
	}

	if (extension == "jpg" || extension == "jpeg") {
		return "image/jpeg";
	}

	if (extension == "webp") {
		return "image/webp";
	}

	return "application/octet-stream";
}

bool csd::ResponseFactory::text(csd::Response& resp, const std::string & txt) {
	resp.setVersion(1);
	resp.setStatus(200);
	setDefaultHeaders(resp);
	resp.setHeader("Content-Type", "text/plain");
	resp.setBody(txt);
	return true;
}

bool csd::ResponseFactory::redirect(csd::Response& resp, const std::string & url) {
	resp.setVersion(1);
	resp.setStatus(301);
	setDefaultHeaders(resp);
	resp.setHeader("Location", url);
	resp.setBody("Redirecting...");
	return true;
}

bool csd::ResponseFactory::sendFile(csd::Response & resp, const std::string & path) {
	csd::Buffer fileBuffer = csd::nullBuffer();

	std::ifstream file(path, std::ios::binary | std::ios::ate);

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	if (!file || size < 0) {
		error(resp, 404);
		return true;
	}

	csd::makeEmptyBuffer(&fileBuffer, size);

	if (file.read(fileBuffer.data, size)) {
		resp.setBody(fileBuffer);
	} else {
		error(resp, 500);
	}

	setDefaultHeaders(resp);

	resp.setHeader("Content-Type", getMimeType(getExtensionFromPath(path)));

	csd::freeBuffer(&fileBuffer);

	file.close();

	return true;
}

bool csd::ResponseFactory::downloadFile(csd::Response & resp, const std::string & path) {
	setDefaultHeaders(resp);
	sendFile(resp, path);
	resp.setHeader("Content-Disposition", "attachment");
	return true;
}

bool csd::ResponseFactory::error(csd::Response & resp, int statusCode) {
	resp.setStatus(statusCode);
	setDefaultHeaders(resp);
	resp.setBody(std::to_string(statusCode) + " " + csd::Response::makeStatusMessage(statusCode));
	return true;
}

void csd::ResponseFactory::setDefaultHeaders(csd::Response & resp) {
	resp.setHeader("Accept-Ranges", "bytes");
	resp.setHeader("Date", getHttpDate());
}
