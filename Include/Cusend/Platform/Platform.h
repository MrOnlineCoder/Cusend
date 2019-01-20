/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_PLATFORM_H
#define CSD_PLATFORM_H

#ifdef _WIN32

#include <winsock2.h>
typedef int socklen_t;

#else 

#define INADDR_ANY      0x00000000
#define INADDR_NONE     0xFFFFFFFF
#define SOCKET_ERROR	(-1)
#define INVALID_SOCKET  -1
#define SOCKET int

#include <sys/socket.h>
#include <arpa/inet.h>

#endif

namespace csd {
	class Platform {
	public:
		static bool preInitSockets();
		static void closeSocket(SOCKET sock);
		static void shutdownSocket(SOCKET sock);
		static int getLastSocketError();
		static void startThread(void* fn, void* arg);
	};
}

#endif // !CSD_PLATFORM_H
