/**
 *
 *  @brief     Layout agnostic functions to read DSV files - with convenience for CSV and TSV
 *  @details   Formats that use delimiter-separated values (DSV) store two-dimensional arrays of data by separating the values in each row with specific delimiter characters. 
 *			   Simple functions convert the DSV data into a single column table of tokens.
 *			   This can then be subdivided by the caller with domain specific information and sanitized.
 *  @author    Jeremy Thornton
 *  @date      13.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef FSYS_READ_DSV_H
#define FSYS_READ_DSV_H

#include "fsys_constants.h"

namespace fsys {

	int read_dsv(const char* file_path, char data_table[][MAX_LINE_SIZE], uint16_t row_count, const char delim, bool is_strip = true) {
		int i = 0;	
		char row[MAX_LINE_SIZE];
		char* token;

		FILE* fptr = fopen(file_path, "r");
		if (!fptr) return STDIO_FAIL;
		
		while (fgets(row, MAX_LINE_SIZE, fptr)) {	// read each line
			token = strtok(row, &delim);			// split out the first token
			while (i < row_count					// do not overrun the data table			
				&& token != NULL					// valid token
				&& *token != LFEED					// not a CRLF
				&& *token != CRETURN) {				// if valid and whilst line has more tokens
				if (is_strip) {						// store in data table
					assert(sscanf(token, " %s", data_table[i++]));	// strip leading whitespaces " %s"
				}
				else {
					assert(sscanf(token, "%s", data_table[i++]));	// note the absence of leading space "%s"
				}
				token = strtok(NULL, ",");			// split out the next token
			}
		}

		fclose(fptr);
		return i;
	}

}

#endif