/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      20.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_MODE7_H
#define TEST_MODE7_H

#include <iostream>
#include <cassert>

#include "../../../bios/bios_services.h"

#include "mda_mode7.h"
#include "mda_mode7_write_character.h"
#include "mda_mode7_write_attribute.h"
#include "mda_mode7_write_pixel.h"
#include "mda_mode7_cls.h"
#include "mda_mode7_fill_area.h"
#include "mda_mode7_draw_vertical_line.h"
#include "mda_mode7_draw_vertical_capped_line.h"
#include "mda_mode7_write_bitmap.h"

#include "../../gfx_bitmap.h"

using namespace bios;
using namespace mda::mode7;
using namespace attribute;

namespace test_mode7 {

	void run() {

		std::cout
			<< bios::video_adapter_names[bios::detect_video_adapter_type()] << "\n"
			<< bios::video_mode_names[bios::get_video_state().mode] << "\n"
			<< "test IBM Monochrome Display Adapter (MDA)...\n";
		wait_key_ascii();
		enter();
		std::cout << "mode " << bios::video_mode_names[bios::get_video_state().mode] << "\n";

		/* {
			std::cout << (char) colour::gray << std::endl;
			screen_bound::write_character(10, 10, 'A');
			screen_bound::write_character(10, 11, 'A', invisible);
			screen_bound::write_character(10, 12, 'A', underline);
			screen_bound::write_character(10, 13, 'A', normal);
			screen_bound::write_character(10, 14, 'A', bright);
			screen_bound::write_character(10, 15, 'A', blink);
			screen_bound::write_character(10, 16, 'A', reverse);
			screen_bound::write_character(10, 17, 'A', reverse_bright);
			screen_bound::write_character(10, 18, 'A', reverse_blink);
			screen_bound::write_character(10, 19, 'A', bright_blink);
			wait_key_ascii();
			screen_bound::write_attribute(10, 11, 'A', bright_blink);
			wait_key_ascii();
			cls_attributes();
			wait_key_ascii();
			cls_attributes(blink);
			wait_key_ascii();
			cls_characters('*');
			wait_key_ascii();
			cls();
		}*/
		/* {
			cls();
			wait_key_ascii();
			cls(colour::light_gray);
			wait_key_ascii();
			cls(colour::gray);
			wait_key_ascii();
			cls(colour::dark_gray);
			wait_key_ascii();
			cls(colour::white);
			wait_key_ascii();
			cls(colour::light_gray, attribute::bright);
			wait_key_ascii();
			cls(colour::gray, attribute::bright);
			wait_key_ascii();
			cls(colour::dark_gray, attribute::bright);
			wait_key_ascii();
			cls(colour::white, attribute::bright);
		}*/
		/* {
			wait_key_ascii();
			cls();
			screen_bound::write_pixel(40, 10, colour::dark_gray);
			screen_bound::write_pixel(40, 11, colour::gray);
			screen_bound::write_pixel(40, 12, colour::light_gray);
			screen_bound::write_pixel(40, 13, colour::white);
		}*/
		/*{
			wait_key_ascii();
			for (int i = 0; i < 25; ++i) {				
				screen_bound::fill_area(i, i, 10, 10, 0xDB);
				wait_key_ascii();
				screen_bound::fill_area(i, i, 10, 10, 0);				
			}	
		}*/
		/* {
			wait_key_ascii();
			screen_bound::draw_vertical_line(10, 1, 10, 20);
			screen_bound::draw_vertical_capped_line(11, 1, 11, 20);
			screen_bound::draw_vertical_line(12, 2, 12, 19);
			screen_bound::draw_vertical_capped_line(13, 2, 13, 19);
			screen_bound::draw_vertical_line(20, 10, 20, 12);
			screen_bound::draw_vertical_capped_line(21, 10, 21, 12);
			screen_bound::draw_vertical_line(22, 10, 22, 11);
			screen_bound::draw_vertical_capped_line(23, 10, 23, 11);
		}*/
		{
			wait_key_ascii();
			uint8_t bmp_data[30] = {
				'-', reverse, '-', reverse, '-', reverse,
				MEDIUM_SHADE, reverse, MEDIUM_SHADE, reverse, MEDIUM_SHADE, reverse,
				MEDIUM_SHADE, reverse, MEDIUM_SHADE, reverse, MEDIUM_SHADE, reverse,
				MEDIUM_SHADE, reverse, MEDIUM_SHADE, reverse, MEDIUM_SHADE, reverse,
				'-', reverse, '-', reverse, '-', reverse
			};
			gfx::bitmap bmp(3, 5, COLOUR_DEPTH, bios::TEXT_MONOCHROME_80X25, bmp_data);
			screen_bound::write_bitmap(10, 10, &bmp);
			std::cout << std::hex << &bmp_data << std::endl;
		}
		wait_key_ascii();
		exit();
		std::cout << "mode " << bios::video_mode_names[bios::get_video_state().mode] << "\n";
		std::cout << "success!\n";
	}

}

#endif