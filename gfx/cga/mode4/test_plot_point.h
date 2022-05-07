/**
 *
 *  @file      test_plot_point.h
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_PLOT_POINT_H
#define TEST_PLOT_POINT_H

#include <iostream>
#include <cassert>
#include <cmath>

#include "../../../system/detect.h"
#include "../../../bios/bios_video_services.h"
#include "../../../jtl/array.h"

#include "cga_mode4.h"
#include "cga_mode4_plot_point.h"


namespace test_plot_point {

	const double PI = 3.14159;

	void f(cga::mode4::colour_t colour) {
		double w = 141;
		double h = 141;
		double xstep = 1;
		double ystep = 3;
		double delta = 70;
		double k = 80;
		double factor = -0.001;
		jtl::size_t xnudge = 70;
		jtl::size_t ynudge = 180;
		jtl::array<jtl::size_t, 255> m;
		m.clear();

		double a = std::cos(PI / 4);
		for (double y = 1; y < h; y += ystep) {
			double e = a * y;
			double c = y - delta;
			c = c * c;
			for (double x = 1; x < w; x += xstep) {
				double d = x - delta;
				double z = k * std::exp(factor * (c + d * d));
				jtl::size_t x1 = static_cast<jtl::size_t>(x + e);
				jtl::size_t y1 = static_cast<jtl::size_t>(z + e);
				if (y1 >= m[x1]) {
					m[x1] = y1;
					cga::mode4::screen_bound::plot_point(x1 + xnudge, ynudge - y1, colour);
				}
			}
		}
	}

	void run() {
		//assert(system::detect_8087());
		cga::mode4::enter();
		cga::mode4::print_mode_info();
		
		std::cout << "test plot_point... ";
		{
			
			f(cga::mode4::colour::cyan);
			f(cga::mode4::colour::magenta);
			f(cga::mode4::colour::white);
			std::getchar();
			cga::mode4::palette_cyan_red_white();
			f(cga::mode4::colour::cyan);
			f(cga::mode4::colour::red);
			f(cga::mode4::colour::white);
			std::getchar();
			cga::mode4::palette_green_red_yellow();
			f(cga::mode4::colour::green);
			f(cga::mode4::colour::red);
			f(cga::mode4::colour::yellow);
		}
		{
			std::getchar();
			for (jtl::size_t y = 0; y < SCREEN_Y_MAX; ++y) {
				for (jtl::size_t x = 0; x < SCREEN_X_MAX; ++x) {
					cga::mode4::torus_bound::plot_point(x, y, cga::mode4::colour::cyan);
				}
			}
		}
		std::cout << "success!\n";
		std::cout << "\nPress <ENTER>";
		std::getchar();
		cga::mode4::exit();
		cga::mode4::print_mode_info();
	}

}

#endif