/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_COMMON_H
#define CSD_COMMON_H

#include <cstdint>
#include <cctype>

#include <string>

namespace csd {
	std::string toUpperCase(std::string& str);
	std::string decodeURI(std::string& uri);
}

#endif // !CSD_COMMON_H
