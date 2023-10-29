/**
 *
 *  @file      dos_services_files.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "dos_services_files.h"

namespace dos {


	/**
	* INT 21,36 - Get Disk Free Space
	* AH = 36h
	* DL = drive number (0=default, 1=A:)
	* 
	* on return:
	* AX = sectors per cluster
	*    = FFFF if drive is invalid
	* BX = number of available clusters
	* CX = number of bytes per sector
	* DX = number of clusters per drive
	* 
	* - used to determine available space on specified disk
	* - see	INT 21,1B   INT 21,1C
	*/
	void get_disk_free_space(uint16_t drive_number, disk_space_info_t* info) {
		__asm {
			.8086
			les		di, info 
			
			stosw 
			xor		ax, ax
			stosw
			stosw
			stosw
		}
	}

}