/**
 *
 *  @file      test_bitmap.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      26.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_BITMAP_H
#define TEST_BITMAP_H

#include <iostream>
#include <cassert>
#include <stdio.h>

#include "cga_mode6_bitmap.h"

namespace test_bitmap {

	void run() {
		std::cout << "test_bitmap... ";
		{
			cga::mode6::bitmap<1, 8, 8> bmp;
			std::cout
				<< bmp.width() << ' '
				<< bmp.height() << ' '
				<< bmp.word_width() << ' '
				<< bmp.size() << ' '
				<< bmp.pixels().size() << ' '
				<< bmp.pixels().paragraphs() << ' '
				<< '\n';
			printf("%#p\n", bmp.pixels().data_address().address);
			bmp.fill(0xFF);
			bmp.draw_to_screen(100, 100);
		}
		std::cout << "success!\n";
	}

}

#endif