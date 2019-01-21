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
	//TODO: define what csd::Buffer is and what is not, they are used strangely in the code now
	/*
	* \brief Helper struct for dynamic memory buffers
	*/
	struct Buffer {
		char* data; /*!< Actual pointer to the data*/
		uint32_t size; /*!< Amount of memory allocated (bytes)*/

		uint32_t usedSize; /*!< Amount of used memory (bytes)? Usually it should be equal to the size*/
	};

	/*
	* \brief Allocates memory for buffer of given size
	* Allocates memory chunk with the given size and sets the buffer struct.
	* Do NOT forget to use freeBuffer() later!
	* \param buf Pointer the buffer
	* \param size Amount of bytes to allocate.
	*/
	void makeEmptyBuffer(csd::Buffer* buf, uint32_t size);

	/*
	* \brief Returns a null-buffer
	* Use it for initalizing buffer struct before allocating the memory
	* \return Null-buffer with the size of 0 pointing to the NULL
	*/
	csd::Buffer nullBuffer();

	/*
	* \brief Frees memory allocated for a buffer
	* \param buf Pointer to the buffer which needs to be freed
	*/
	void freeBuffer(csd::Buffer* buf);
}

#endif // !CSD_MEMORY_H
