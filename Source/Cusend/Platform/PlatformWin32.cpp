/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Platform/Platform.h>

bool csd::Platform::preInitSockets() {
	int iResult = 0;

	WSADATA wsaData;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return false;
	}

	return true;
}

void csd::Platform::closeSocket(SOCKET sock) {
	closesocket(sock);
}

void csd::Platform::shutdownSocket(SOCKET sock) {
	shutdown(sock, SD_BOTH);
}

int csd::Platform::getLastSocketError() {
	return WSAGetLastError();
}

void csd::Platform::startThread(void* fn, void * arg) {
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) fn, arg, NULL, NULL);
}
