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
#include "dos_services_constants.h"
#include "dos_error_messages.h"

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
	void get_disk_free_space(uint8_t drive_number, disk_space_info_t* info) {
		__asm {
			.8086
			push	ds
			pushf

			mov		dl, drive_number
			mov		ah, GET_DISK_FREE_SPACE
			int		DOS_SERVICE
			les		di, info
			cmp		ax, DOS_ERROR				; FFFFh invalid drive
			je		ERR

			mov		[di], ax					; sectors per cluster
			mov		[di + 2], bx				; available clusters
			mov		[di + 4], cx				; bytes per sector
			mov		[di + 6], dx				; clusters per drive 
			jmp		END
			
	ERR:	cld
			stosw 
			xor		ax, ax
			stosw
			stosw
			stosw

	END:	popf
			pop		ds
		}

		if (info->sectors_per_cluster == 0xFFFF) {
			std::cout << dos::error::messages[dos::error::INVALID_DRIVE_SPECIFIED];
		}
	}

}