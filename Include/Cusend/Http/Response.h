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
	/*
	* \brief Class represents a response, which should be sent to the HTTP client
	* Use csd::ResponseFactory for generating responses.
	* User should NOT create csd::Response instances by himself.
	* Prepared csd::Responses are passed to the route handler by Cusend automatically.
	*/
	class Response {
	public:
		/*
		* \brief Default constructor
		*/
		Response();

		/*
		* \brief Sets HTTP header in the response
		* \param name Name of the HTTP header (e.g. "Content-Type")
		*/
		void setHeader(const std::string& name, const std::string& value);

		/*
		* \brief Set response body.
		* Sets response body based on the passed string.
		* No further header settings are required, Content-Length is handled automatically by Cusend.
		*/
		void setBody(const std::string& body);

		/*
		* \brief Set response body.
		* Sets response body based on the passed Buffer.
		* Buffer data is copied into own Response buffer
		* \param body Pointer to the buffer
		*/
		void setBody(csd::Buffer& body);

		/*
		* \brief Set HTTP status for the response
		* \param code HTTP status code.
		*/
		void setStatus(int code);

		/*
		* \brief Set HTTP version.
		* It is not recommened to use this method at all.
		* \param ver HTTP version. (0 = 1.0, 1 = 1.1, 2 = 2.0)
		*/
		void setVersion(int ver);

		/**
		* \brief Sets HTTP cookie
		* \param name Cookie name
		* \param value Cookie value
		* \param age (optional) Sets Max-Age property - number of seconds until the cookie expires.
		* \param httpOnly (optional) HTTP-only cookies aren't accessible via JavaScript
		*/
		void setCookie(const std::string& name, const std::string& value, long age=0L, bool httpOnly=false);

		/*
		* \brief Generates response and fills the buffer with the response data
		* User doesn't need to use this method at all, it is more for internal usage.
		*/
		void generate(csd::Buffer& target);

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
