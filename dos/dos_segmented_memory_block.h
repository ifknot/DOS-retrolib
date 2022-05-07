/**
 *
 *  @file      segmented_memory_block.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef SEGMENTED_MEMORY_BLOCK_H
#define SEGMENTED_MEMORY_BLOCK_H

#include <stdint.h>
#include <iostream>

#include "../jtl/size_t.h"

#include "dos_services.h"
#include "dos_services_types.h"

namespace dos {

	template<typename T>
	class segmented_memory_block {

	public:

		typedef jtl::size_t size_type;

		/**
		*  @brief segmented_memory_block object constructor
		* 
		*  @note A paragraph is an area of memory of 16 bytes in size. 
		*  x86 real mode segments start on paragraph boundaries by Intel design.
		*  @param requested size (bytes)
		*/
		segmented_memory_block(size_type size) :
			size_(size),
			paragraphs_((size / PARAGRAPH_SIZE) + ((size & 0xF) ? 1 : 0)),  // ? need extra paragraph for any remainder
			data_(allocate_memory_blocks(paragraphs_), 0)
		{}

		~segmented_memory_block() {
			free_allocated_memory_blocks(data_.memory.segment);
			std::cout << "deallocated " << paragraphs_ << " paragraphs\n";
		}

		inline T& operator[](size_type i) {
			return *reinterpret_cast<T*>(data_.address + i);
		}

		void clear() {
			fill(0);
		}

		void fill(T n) {
			for (int i = 0; i < size_; ++i) {
				operator[](i) = n;
			}
		}

		inline size_type size() {
			return size_;
		}

		inline size_type paragraphs() {
			return paragraphs_;
		}

		inline address_t data_address() {
			return data_;
		}

		/**
		*  @brief display the contents of the 16 byte Memory Control Block (MCB) for this memory block
		*
		* MCB - DOS Memory Control Block
		* Offset	Size	Description
		* 00		byte	'M' 4Dh  member of a MCB chain, (not last)
		*					'Z' 5Ah  indicates last entry in MCB chain
		*					other values cause "Memory Allocation Failure" on exit
		* 01		word	PSP segment address of MCB owner (Process Id)
		*					possible values:
		*						0		= free
		*						8		= Allocated by DOS before first user pgm loaded
		*						other	= Process Id/PSP segment address of owner
		* 03		word	number of paras related to this MCB (excluding MCB)
		* 05		11 bytes	reserved
		* 08		8bytes	ASCII program name, NULL terminated if less than max length (DOS 4.x+)
		*					Note: Prior to DOS 4.0, this field contained garbage.
		* 10		nbytes	first byte of actual allocated memory block
		*
		* - to find the first MCB in the chain, use  INT 21,52
		* - DOS 3.1+ the first memory block contains the DOS data segment
		*   ie., installable drivers, buffers, etc
		* - DOS 4.x the first memory block is divided into subsegments,
		*   with their own memory control blocks; offset 0000h is the first
		* - the 'M' and 'Z' are said to represent Mark Zbikowski
		* - the MCB chain is often referred to as a linked list, but technically isn't.
		*/
		void debug() {
			address_t mcb = data_;
			mcb.memory.segment--; //x86 real mode decrement a segment register by one moves 16 bytes paragraph - the size of the MCB.
			char* p = (char*)mcb.address;
			std::cout << "\nMCB - DOS Memory Control Block\nOffset\tSize\tValue\n"
				<< "00\tbyte\t" << *p << '\n'
				<< "01\tword\t" << *(size_type*)(p + 1) << '\n'
				<< "03\tword\t" << *(size_type*)(p + 3) << '\n'
				<< "05\t11bytes\treserved\n"
				<< "08\t8bytes\t";
			int i = 8;
			while (p[i] != 0 && i < 16) std::cout << p[i++];
			std::cout << std::endl;
		}

	private:

		size_type size_;
		size_type paragraphs_;
		address_t data_;

	};

}

#endif