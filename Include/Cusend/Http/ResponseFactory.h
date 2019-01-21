/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_RESPONSEFACTORY_H
#define CSD_RESPONSEFACTORY_H

#include <Cusend/Http/Response.h>

namespace csd {
	/**
	* \brief Class with static functions which will generate different types of responses
	*/
	class ResponseFactory {
	public:
		/**
		* \brief Makes plaintext response.
		* The Content-Type is set to text/plain and the body will consits of passed string.
		* \param resp Target response object
		* \param txt Text content of the response
		*/
		static bool text(csd::Response& resp, const std::string& txt);
		
		/**
		* \brief Redirects the HTTP client.
		* Redirect is achieved by using Location header. Status code is set to 301 Moved Permanently.
		* \param resp Target response object
		* \param url Target URL
		*/
		static bool redirect(csd::Response& resp, const std::string& url);

		/**
		* \brief Reads and sends file contents (serve static content).
		* The Content-Type value will be based on the file extension.
		* If there was an error reading the file, it will form a "500 Internal Server Error" page
		* If file is not found, it will form a "404 Not Found" page
		* \param resp Target response object
		* \param path Relative path to the file.
		*/
		static bool sendFile(csd::Response& resp, const std::string& path);

		/**
		* \brief Sends file for download.
		* Usually, this will result in browser asking user to download the file and showing "Save as.." dialog.
		* The Content-Type value will be set as application/octet-stream.
		* The Content-Disposition is set to "attachment"
		* Same error handling cases apply as for sendFile()
		* \param resp Target response object
		* \param path Relative path to the file.
		*/
		static bool downloadFile(csd::Response& resp, const std::string& path);

		/**
		* \brief Generates a simple error page.
		* The page will consists of text "XXX y" where XXX is the HTTP error status code and "y" is the status code description, e.g. Not Found for 404
		* This function is used by sendFile/downloadFile to handle file reading errors.
		* \param resp Target response object
		* \param statusCode HTTP status code of the desired error.
		*/
		static bool error(csd::Response& resp, int statusCode);
	private:
		static void setDefaultHeaders(csd::Response& resp);
	};
}

#endif // !CSD_RESPONSEFACTORY_H
