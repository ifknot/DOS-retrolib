/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef FPEEK_H
#define FPEEK_H

#include <stdio.h>


namespace filesys {

	char fpeek(FILE* fptr) {
		char chr; 
		chr = getc(fptr);			// read one byte from the stream
		fseek(fptr, -1, SEEK_CUR);	// step back one byte in the stream
		return chr;
	}

}

#endif