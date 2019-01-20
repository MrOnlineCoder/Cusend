/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_ERROR_H
#define CSD_ERROR_H

namespace csd {
	typedef unsigned int Error;

	namespace Errors {
		const Error None = 0;
		const Error PlatformSocketInitFailed = 1;
		const Error SocketCreateFailed = 2;
		const Error BindSocketFailed = 3;
		const Error ListenSocketFailed = 4;
	}
}

#endif // !CSD_ERROR_H
