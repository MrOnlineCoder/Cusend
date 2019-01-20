/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#include <Cusend/Core/Memory.h>

#include <cstring>

void csd::makeEmptyBuffer(Buffer * buf, uint32_t size) {
	buf->data = new char[size];
	buf->size = size;
	buf->usedSize = 0;

	std::memset(buf->data, 0, size);
}

csd::Buffer csd::nullBuffer() {
	Buffer buff;
	buff.size = 0;
	buff.usedSize = 0;
	buff.data = NULL;

	return buff;
}

void csd::freeBuffer(Buffer * buf) {
	if (buf->size == 0) return;

	delete[] buf->data;
	buf->size = 0;
	buf->usedSize = 0;
}
