#include <iostream>

#include "RETROLIB/test_retrolib.h"

/**
* @todo 
* [x] hga::graphics:: is hga and hga is mda
* [] btimap file tools separate
* [] bmp_x_offsets_t
* [] make_bmp_x_offsets(gfx::bitmap_t* bmp, bmp_x_offsets_t* bmpoff)
* 
* 
* Use the bitmap palette ptr to address hcg::graphics::bmp_x_offsets_t
* HCG bitmap expects a bitmap with 8 horizontal single pixel x-steps offset images for the each sprite animation frames
* NB animation frames are ordered vertically
* this would be same column,row layout for CGA 600x200 mode, whereas CGA 320x200 mode would be 4 horizontal offsets 
* e.g. 32x32 pixel frame would need 40x32 pixels per frame with 8 offsets being 320 pixels the nearest pwoer of 2 width then 512 pixels ie 64bytes wide 
* leaving 64K image map 1024 vertical pixels which for the 32x32 frame example would be a maximum of 32 animation frames 
* whilst memory consuming this approach enables fast animation using precalcuated offset frames for x 0..7 positions
* 
* [] plot_pixel
* [] hsync_plot_pixel
* [] read_pixel
* [] hline (fast)
* [] vline (fast)
* [] rectangle (fast)
* [] line (bresenham)
* [] circle
* [] elipse
*/

int main() {
	
	test_retrolib::run();

	return 0;

}
