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
	void get_disk_free_space(uint8_t drive_number, file::disk_space_info_t* info) {
		__asm {
			.8086
			push	ds
			pushf

			mov		dl, drive_number
			mov		ah, GET_DISK_FREE_SPACE
			int		DOS_SERVICE
			cmp		ax, DOS_ERROR				; FFFFh invalid drive
			jne		OK

			cld
			les		di, info
			stosw								; store the error marker
			xor ax, ax
			stosw								; zero the rest of info struct
			stosw
			stosw
			jmp		END

	OK:		lds		di, info
			mov		[di], ax					; sectors per cluster
			mov		[di + 2], bx				; available clusters
			mov		[di + 4], cx				; bytes per sector
			mov		[di + 6], dx				; clusters per drive 

	END:	popf
			pop		ds
		}

		if (info->sectors_per_cluster == 0xFFFF) {
			std::cout << dos::error::messages[dos::error::INVALID_DRIVE_SPECIFIED] << std::endl;
		}
	}
	/**
	* INT 21, 3C - Create File Using Handle
	* AH = 3C
	* CX = file attribute(see FILE ATTRIBUTES)
	* DS:DX = pointer to ASCIIZ path name
	* 
	* on return :
	* CF = 0 if successful
	*    = 1 if error
	* AX = files handle if successful
    *    = error code if failure(see DOS ERROR CODES)
	* 
	* @note - if file already exists, it is truncated to zero bytes on opening
	*/
	file::handle_t create_file_using_handle(char* path_name, uint16_t file_attributes) {
		file::handle_t handle;
		uint16_t err_code = 0;
		__asm {
			.8086
			push	ds
			pushf

			lds		dx, path_name
			mov		cx, file_attributes
			mov		ah, CREATE_FILE_USING_HANDLE
			int		DOS_SERVICE
			jnc		OK
			mov		err_code, ax
			xor		ax,ax
	OK:		mov		handle, ax

	END:	popf
			pop		ds
		}

		if (err_code) {
			std::cout << dos::error::messages[err_code] << std::endl;
		}

		return handle;
	}

}