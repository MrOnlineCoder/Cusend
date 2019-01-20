/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Http/Server.h>

#include <Cusend/Platform/Platform.h>


csd::Server::Server() {
	m_socket = INVALID_SOCKET;
}

csd::Server::~Server() {
	csd::Platform::closeSocket(m_socket);
}

bool csd::Server::createSocket() {
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	return m_socket != -1;
}

bool csd::Server::bind(uint16_t port) {
	//TODO: make more Unix-friendly
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(port);
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;

	int err = ::bind(m_socket, (struct sockaddr *) &m_addr, sizeof(m_addr));

	if (err < 0) {
		return false;
	} else {
		return true;
	}
}

bool csd::Server::listen() {
	return ::listen(m_socket, SOMAXCONN) != SOCKET_ERROR;
}

void csd::Server::acceptNextClient(NetworkClient* target) {
	target->socket = ::accept(m_socket, (struct sockaddr *) &(target->ip), NULL);
}

int csd::Server::receiveIntoBuffer(NetworkClient & client, Buffer & buff) {
	int bytes = ::recv(client.socket, buff.data, buff.size, 0);
	buff.usedSize = bytes;

	return bytes;
}
