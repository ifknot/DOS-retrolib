#ifndef HGA_MONOSPACED_FONT_T_H
#define HGA_MONOSPACED_FONT_T_H

#include <stdint.h>
#include <string>

namespace hga {

	template<int BYTES, int CHAR_COUNT = 256>
	struct monospaced_font_t {

		monospaced_font_t(char(*font_data)[BYTES]) : data(font_data) {
			//data = new uint8_t[CHAR_COUNT][BYTES];
		}

		const char(*data)[BYTES];

	};

}

#endif