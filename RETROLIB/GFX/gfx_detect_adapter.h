/**
 *
 *  @brief     Detect graphics adapter card type for single/dual headed system
 *  @url	   https://www.seasip.info/VintagePC/dualhead.html
 *  @details   To have a dual-head system, must be one colour card and one mono (or Hercules InColor, or 8514/A) card. 
 *  If your PC has video hardware on its motherboard, that will usually count as one of the cards; 
 *  If it can't be disabled then it certainly will.
 *  If both cards are on the ISA bus, then they need to be both 8-bit or both 16-bit; since all known CGA,
 *  MDA and Hercules cards are 8-bit this means that both cards must be 8-bit. 
 *  The ATI appnote explains why. 
 *  This restriction may not apply if the VGA card uses MCA, VESA, PCI or AGP(?)
 *  @note IBM's manual warns that on an original PC with both MDA and CGA, the MDA card must be set as the 
 *  primary display (so that the BIOS initialises it) or the mono monitor may be damaged. 
 *  @author    Jeremy Thornton
 *  @date      4.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef GFX_DETECT_ADAPTER_H
#define GFX_DETECT_ADAPTER_H

#include <stdint.h>

namespace gfx {

	uint8_t detect_monochrome_adapter();

	uint8_t detect_colour_adapter();

	inline uint8_t detect_color_adapter() {
		return detect_colour_adapter();
	}

	uint8_t detect_adapter();

}

#endif