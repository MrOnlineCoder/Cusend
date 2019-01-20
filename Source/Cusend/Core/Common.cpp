/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Core/Common.h>

std::string csd::toUpperCase(std::string & str) {
	std::string res = "";

	for (std::size_t i = 0; i < str.size(); i++) {
		res += std::toupper(str[i]);
	}

	return res;
}
