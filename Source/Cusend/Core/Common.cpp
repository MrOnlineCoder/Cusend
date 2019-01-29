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

std::string csd::decodeURI(std::string & uri) {
	std::string s;

	for (std::size_t i = 0; i < uri.size(); i++) {
		char c = uri[i];
		
		if (c == '+') {
			s.push_back(' ');
			continue;
		}

		if (c == '%') {
			if (i + 2 > uri.size()) {
				continue;
			}

			char hex[3];

			hex[0] = uri[++i];
			hex[1] = uri[++i];
			hex[2] = '\0';

			char newChar = (char)(int) strtol(hex, NULL, 16);

			s.push_back(newChar);
			continue;
		}

		s.push_back(c);
	}


	return s;
}
