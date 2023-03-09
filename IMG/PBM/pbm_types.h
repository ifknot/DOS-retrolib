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

#include "pbm_constants.h"

// TODO:
// [ ] memory managing bitmap class

namespace pbm {

	/**
	 *  @struct header_t
	 *  @brief  PBM is monochrome 1 bit per pixel
	 */
	struct header_t {			
		uint16_t magic_number;
		uint16_t width;
		uint16_t height;
	};

	struct bitmap {
		header_t header;
		uint8_t* data;

		/*
		bitmap(std::string file_path) {

		}

		~bitmap_t() {
			delete data;
		}
		*/
	};

}

#endif