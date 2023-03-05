#ifndef HGA_MONOSPACED_FONT_T_H
#define HGA_MONOSPACED_FONT_T_H

#include <stdint.h>
#include <string>

namespace hga {

	template<int WIDTH>
	struct monospaced_font_t {

		const uint8_t(*data)[WIDTH];

	};

}

#endif