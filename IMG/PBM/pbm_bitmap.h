/**
 *
 *  @brief     Portable Bit Map -The PBM format is a lowest common denominator monochrome file format.
 *  @details   Each PBM image consists of the following:
 *  A "magic number" for identifying the file type. A pbm image's magic number is the two characters "P4".
 *  Whitespace (blanks, TABs, CRs, LFs).
 *  The width in pixels of the image, formatted as ASCII characters in decimal.
 *  Whitespace.
 *  The height in pixels of the image, again in ASCII decimal.
 *  A single whitespace character (usually a newline).
 *  A raster of Height rows, in order from top to bottom. 
 *  Each row is Width bits, packed 8 to a byte, with don't care bits to fill out the last byte in the row. 
 *  Each bit represents a pixel: 1 is black, 0 is white. 
 *  The order of the pixels is left to right. 
 *  The order of their storage within each file byte is most significant bit to least significant bit.
 *  The order of the file bytes is from the beginning of the file toward the end of the file.
 *  A row of an image is horizontal. A column is vertical. 
 *  The pixels in the image are square and contiguous.
 *  Before the whitespace character that delimits the raster, any characters from a "#" through the next carriage return or newline character, is a comment and is ignored. Note that this is rather unconventional, because a comment can actually be in the middle of what you might consider a token. Note also that this means if you have a comment right before the raster, the newline at the end of the comment is not sufficient to delimit the raster.
 *  @url https://netpbm.sourceforge.net/doc/pbm.html
 *  @author    Jeremy Thornton
 *  @date      11.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef PBM_BITMAP_H
#define PBM_BITMAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <bitset>

#include "../../FILESYS/filesys.h"
#include "../../DOS/dos_error_messages.h"

#include "pbm_constants.h"
#include "pbm_create_ifstream.h"

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

	class bitmap {

	public:
		
		bitmap(std::string file_path) {
			header_.file_path = file_path;
			std::ifstream* f = create_ifstream(header().file_path);
			read(*f);
			f->close();
			delete f;
		}

		void write(std::ostream& os) const {
			os << header_.file_path.c_str() << ' '
				<< std::hex << header_.magic_number << std::dec << ' '
				<< header_.width << ' '
				<< header_.height << ' '
				<< header_.bytes << ' '
				<< header_.offset << ' '
				<< header_.size << std::hex << '\n';
			for (int i = 0; i < header_.bytes; ++i) {
				std::bitset<8> byte(data_[i]);
				os << byte[0] << byte[1] << byte[2] << byte[3] << byte[4] << byte[5] << byte[6] << byte[7] << '\n'; // TODO: fix the layout
			}
		}

		void read(std::istream& is) {
			char line[MAX_LINE_SIZE];
			is.getline(line, MAX_LINE_SIZE);
			if (is.eof()) {						// 1. is there at least 1 line in the file?
				header_.file_path += dos::error::messages[dos::error::INVALID_DATA];
				return;
			}
			if (*(uint16_t*)line != MAGIC_P4) { // 2. is it a valid magic number?
				header_.file_path += dos::error::messages[dos::error::INVALID_FORMAT];
				return;
			}
			header_.magic_number = MAGIC_P4;
			while (is.peek() == '#') is.ignore(MAX_LINE_SIZE, '\n');	// skip any comments
			is >> header_.width >> header_.height;
			header_.bytes = (int)header_.width / 8;						// convert width to bytes
			header_.bytes += (header_.width & 7) == 0 ? 0 : 1;			// need an extra byte for width remainder < 8?
			header_.bytes *= header_.height;							// expected number bytes
			is.ignore(MAX_LINE_SIZE, '\n');								// data should start on next line
			header_.offset = is.tellg();								// data starts here
			is.seekg(0, is.end);										// seek to the end
			header_.size = is.tellg();									// position of the current character ie the end character
			is.seekg(header_.offset);								// return to the data
			if (header_.offset + header_.bytes != header_.size) {		// expected amount of data?
				header_.file_path += dos::error::messages[dos::error::INVALID_DATA];
				return;
			}
			data_ = new char[header_.bytes];
			
			is.read(data_, 8);
		}

		header_t& header() {
			return header_;
		}

		char* data() {
			return data_;
		}

		~bitmap() {
			delete data_;
		}
	
	private:

		header_t header_;
		char* data_;
	
	};

}

std::ostream& operator<<(std::ostream& os, const pbm::bitmap& bmp) {
	bmp.write(os);
	return os;
}

std::istream& operator>>(std::istream& is, pbm::bitmap& bmp) {
	bmp.read(is);
	return is;
}

#endif