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
	class ResponseFactory {
	public:
		static bool text(csd::Response& resp, const std::string& txt);
		static bool redirect(csd::Response& resp, const std::string& url);
		static bool sendFile(csd::Response& resp, const std::string& path);
		static bool downloadFile(csd::Response& resp, const std::string& path);

		static bool error(csd::Response& resp, int statusCode);
	private:
		static void setDefaultHeaders(csd::Response& resp);
	};
}

#endif // !CSD_RESPONSEFACTORY_H
