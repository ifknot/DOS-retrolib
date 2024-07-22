#include <iostream>

#include "RETROLIB/test_retrolib.h"

/**
* @todo 
* [] hga::video_modes.h 
* [] hga::vram_buffer.h (cls etc) 
* 	
* [] hga::mem_buffer
* 	[] 
* [x] video block transfer (vblt) functions RAM -> VRAM
*	[x] fullscreen rect 
*	[x] RAM rect A to VRAM A
*	[x] RAM rect A to VRAM rect B
* [x] btimap file tools separate
* [] plot_pixel
* [] hsync_plot_pixel
* [] read_pixel
* [] hline (fast)
* [] vline (fast)
* [] draw_rectangle (fast)
* [] fill_rectangle (hline x height)
* [] line (bresenham)
* [] circle
* [] elipse
*/

int main() {
	
	test_retrolib::run();

	return 0;

}
