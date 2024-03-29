/**
 *
 *  @brief     Tools for Monochrome Portable Bitmap (PBM) file format 
 *  @details   The PBM format was invented by Jef Poskanzer in the 1980s as a format that allowed monochrome bitmaps 
 *             to be transmitted within an email message as plain ASCII text, allowing it to survive any changes in 
 *			   text formatting.
 *  @note      The "magic number" (Px) at the beginning of a file determines the type, not the file extension, 
			   although it is best practice to use the right extension if possible.
 *	@url	   https://en.wikipedia.org/wiki/Netpbm
 *  @author    Jeremy Thornton
 *  @date      9.03.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef PORTABLE_BITMAP_FORMAT_H
#define PORTABLE_BITMAP_FORMAT_H

#include "pbm_constants.h"
#include "pbm_types.h"
#include "pbm.create_simple_bitmap.h"

/**
 *  @namespace pbm
 *  @brief     
 */
namespace pbm {

}

#endif