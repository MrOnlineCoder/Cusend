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
	typedef std::unordered_map<std::string, std::string> RequestMap;

	/**
	* \brief Helper constants for HTTP methods
	*/
	namespace Methods {
		const std::string Get = "GET";
		const std::string Post = "POST";
		const std::string Put = "PUT";
		const std::string Delete = "DELETE";
	};

	/**
	* \brief Class which represents a single request from a HTTP client
	*/
	class Request {
	public:
		int m_httpVersion; /*!< HTTP version of the request. 0 is HTTP/1.0, 1 is HTTP/1.1 and 2 is HTTP/2.0*/
		std::string m_method; /*!< HTTP method*/
		std::string m_url; /*!< Full URL of the request. It includes query parameters. (e.g. /posts?action=show&id=123)*/
		std::string m_ip; /*!< IP of the remote client*/

		RequestMap m_headers; /*!< Map of HTTP headers. Use getHeader() method to receive header's value*/
		RequestMap m_fields; /*!< Map of fields. In GET requests this corresponds to the query string params. In POST it corresponds to the POST-body params*/

		/**
		* \brief Get value of a header
		* Returns value of a HTTP header. 
		* \param name Name of the header (e.g "User-Agent"). Case-insensitive ("user-Agent", "uSeR-AgEnT" are the same)
		* \return Value of the header. If header is not present in the request, empty std::string is returned ("")
		*/
		std::string getHeader(std::string name); 

		/**
		* \brief Get value of a field
		* In GET requests fields are parsed from the query string
		* In POST requests fields are parsed from POST-body
		* \param name Name of the field
		* \return Value of the field. If field is not present in the request, empty std::string is returned ("")
		*/
		std::string getField(const std::string& key);

		/**
		* \brief Get request path
		* Path is the URL without query parameters. 
		* /main/control?action=edit&type=post&id=1 is the full URL
		* /main/control is the path
		*/
		std::string getPath();
	};
}

#endif // !CSD_REQUEST_H
