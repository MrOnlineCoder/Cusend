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
		const Error None = 0; /*!< No error, everything is fine*/
		const Error PlatformSocketInitFailed = 1; /*!< Couldn't initialize OS socket API*/
		const Error SocketCreateFailed = 2; /*!< Couldn't create the socket*/
		const Error BindSocketFailed = 3; /*!< Couldn't bind the socket*/
		const Error ListenSocketFailed = 4; /*!< Couldn't start listening the socket*/
	}
}

#endif // !CSD_ERROR_H
