/**
 *
 *  @brief     MDA toolbox
 *  @details   The Monochrome Display Adapter (MDA, also MDA card, Monochrome Display and Printer Adapter, MDPA) 
 *	is IBM's standard video display card and computer display standard for the IBM PC introduced in 1981. 
 *  The MDA does not have any pixel-addressable graphics modes, only a single monochrome text mode 
 *  which can display 80 columns by 25 lines of high resolution text characters or symbols useful for drawing forms.
 *  @url https://en.wikipedia.org/wiki/IBM_Monochrome_Display_Adapter
 *  @author    Jeremy Thornton
 *  @date      20.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_MODE7_H
#define MDA_MODE7_H

#include "../../../bios/bios_video_services.h"

#include "mda_mode7_constants.h"

namespace mda {

	namespace mode7 {

		static bios::video_mode_t original_mode;

		void enter() {
			original_mode = bios::get_video_state().mode;
			bios::set_video_mode(bios::TEXT_MONOCHROME_80X25);
		}

		void exit(bios::video_mode_t mode = original_mode) {
			bios::set_video_mode(mode);
		}

	}

}

#endif