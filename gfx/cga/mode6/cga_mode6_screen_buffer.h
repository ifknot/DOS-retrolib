/**
 *
 *  @file      cga_mode6_screen_buffer.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      2.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef CGA_MODE6_SCREEN_BUFFER_H
#define CGA_MODE6_SCREEN_BUFFER_H

#include <stdint.h>

#include "../../../jtl/size_t.h"

#include "../cga_constants.h"

namespace cga {

	namespace mode6 {

		typedef jtl::size_t size_type;

		class screen_buffer {

		public:

			screen_buffer() :
				width_(640),
				byte_width_(80),
				height_(200),
				size_(0x4000), // 16K
				buffer_segment_(cga::VIDEO_RAM_SEGMENT),
				pixels_((uint8_t*)((uint32_t)(buffer_segment_) << 16))
			{}

			inline size_type width() {
				return width_;
			}

			inline size_type height() {
				return height_;
			}

			inline size_type byte_width() {
				return byte_width_;
			}

			inline size_type size() {
				return size_;
			}

		private:

			size_type width_;
			size_type height_;
			size_type byte_width_;
			size_type size_;
			uint16_t buffer_segment_;
			uint8_t* pixels_;

		};

	}

}

#endif