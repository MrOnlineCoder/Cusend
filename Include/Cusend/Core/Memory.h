/*
	Cusend Project

	Author: Nikita Kogut (MrOnlineCoder) | github.com/MrOnlineCoder | Telegram @MrOnlineCoder

	License: MIT (see LICENSE for details)

	(c) 2019
*/

#ifndef CSD_MEMORY_H
#define CSD_MEMORY_H

#include <cstdint>

namespace csd {
	struct Buffer {
		char* data;
		uint32_t size;

		uint32_t usedSize;
	};

	void makeEmptyBuffer(csd::Buffer* buf, uint32_t size);

	csd::Buffer nullBuffer();

	void freeBuffer(csd::Buffer* buf);
}

#endif // !CSD_MEMORY_H
