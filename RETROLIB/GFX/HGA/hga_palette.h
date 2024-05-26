/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      24.02.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef HGA_PALETTE_H
#define HGA_PALETTE_H

namespace hga {

	/**
	* @brief black or 'bright' - depending on the monitor colour - i.e. whatever colour the CRT phosphor is
	*/
	enum colours_t {
		BLACK,
		BRIGHT = 0xFFFF	// retrolib gfx uses 16-bit high colours
	};

}

#endif