/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_SERVER_H
#define CSD_SERVER_H

#include <Cusend/Platform/Platform.h>
#include <Cusend/Core/Memory.h>

#include <cstdint>

namespace csd {
	struct NetworkClient {
		SOCKET socket;
		sockaddr_in ip;
	};

	class Server {
	public:
		Server();
		~Server();
		bool createSocket();
		bool bind(uint16_t port);

		bool listen();

		void acceptNextClient(NetworkClient* target);

		int receiveIntoBuffer(NetworkClient& client, Buffer& buff);
	private:
		SOCKET m_socket;
		sockaddr_in m_addr;
	};
}

#endif // !CSD_SERVER_H