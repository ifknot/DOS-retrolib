/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef PBM_TYPES_H
#define PBM_TYPES_H

#include <iostream>
#include <string>

#include "pbm_constants.h"

// TODO:
// [ ] memory managing bitmap class

namespace pbm {

	/**
	 *  @struct header_t
	 *  @brief  PBM is monochrome 1 bit per pixel
	 */
	struct header_t {		
		std::string file_path;
		uint16_t magic_number;
		uint16_t width;		// pixels
		uint16_t height;	// pixels
		uint16_t bytes;		// bytes of data
		uint16_t offset;	// start of data in file
		uint16_t size;		// file size

		header_t() :
			magic_number(0),
			width(0),
			height(0),
			bytes(0),
			offset(0),
			size(0)
		{}
	};

	struct bitmap {
		header_t header;
		char* data;

		/*
		bitmap(std::string file_path) {

		}

		~bitmap_t() {
			delete data;
		}
		*/
	};

}

std::ostream& operator<<(std::ostream& os, const pbm::header_t& header) {
	os << header.file_path.c_str() << ' '
		<< std:: hex << header.magic_number << std::dec << ' '
		<< header.width << ' '
		<< header.height << ' '
		<< header.bytes << ' '
		<< header.offset << ' ' 
		<< header.size << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, pbm::header_t& header) {
	is >> header.magic_number
		>> header.width
		>> header.height;
		
	return is;
}

#endif