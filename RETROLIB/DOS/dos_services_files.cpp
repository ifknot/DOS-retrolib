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
#include "dos_services_types.h"
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
	file::handle_t create_file_using_handle(char* path_name, file::attributes_t create_attributes) {
		file::handle_t fhandle;
		error_code_t err_code = 0;
		__asm {
			.8086
			push	ds
			pushf

			lds		dx, path_name
			mov		cx, create_attributes
			mov		ah, CREATE_FILE_USING_HANDLE
			int		DOS_SERVICE
			jnc		OK
			mov		err_code, ax
			xor		ax,ax
	OK:		mov		fhandle, ax

	END:	popf
			pop		ds
		}

		if (err_code) {
			std::cout << dos::error::messages[err_code] << std::endl;
		}

		return fhandle;
	}

	/**
	* INT 21,3D Open File Using Handle
	* AH = 3D
	* AL = open access mode
	*      00  read only
	*      01  write only
	*      02  read/write
	* DS:DX = pointer to an ASCIIZ file name
	* 
	* on return:
	* AX = file handle if CF not set
	*    = error code if CF set  (see DOS ERROR CODES)
	*/
	file::handle_t open_file_using_handle(char* path_name, uint8_t access_attributes) {
		file::handle_t fhandle;
		error_code_t err_code = 0;
		__asm {
			.8086
			push	ds
			pushf

			lds		dx, path_name
			mov		al, access_attributes
			mov		ah, OPEN_FILE_USING_HANDLE
			int		DOS_SERVICE
			jnc		OK
			mov		err_code, ax
			xor		ax, ax
	OK:		mov		fhandle, ax

	END:	popf
			pop		ds
		}

		if (err_code) {
			std::cout << dos::error::messages[err_code] << std::endl;
		}

		return fhandle;
	}

	/**
	* INT 21,3E - Close File Using Handle
	* AH = 3E
	* BX = file handle to close
	* 
	* on return:
	* AX = error code if CF set  (see DOS ERROR CODES)
	* 
	* - if file is opened for update, file time and date stamp
	*   as well as file size are updated in the directory
	* - handle is freed
	*/
	error_code_t close_file_using_handle(file::handle_t fhandle) {
		error_code_t err_code = 0;
		__asm {
			.8086
			push	ds
			pushf

			mov		bx, fhandle
			mov		ah, CLOSE_FILE_USING_HANDLE
			int		DOS_SERVICE
			jnc		END
			mov		err_code, ax

	END:	popf
			pop		ds
		}

		if (err_code) {
			std::cout << dos::error::messages[err_code] << std::endl;
		}

		return err_code;
	}

	/**
	* INT 21,41 - Delete File
	* AH = 41h
	* DS:DX = pointer to an ASCIIZ filename
	* 
	* on return:
	* AX = error code if CF set  (see DOS ERROR CODES)
	* 
	* - marks first byte of file directory entry with E5 to indicate
	*   the file has been deleted.  The rest of the directory entry
	*   stays intact until reused.   FAT pointers are returned to DOS
	* @note - documented as not accepting wildcards in filename but actually does in several DOS versions
	*/
	error_code_t delete_file(char* path_name) {
		error_code_t err_code = 0;
		__asm {
			.8086
			push	ds
			pushf

			lds		dx, path_name
			mov		ah, DELETE_FILE
			int		DOS_SERVICE
			jnc		END
			mov		err_code, ax

	END:	popf
			pop		ds
		}

		if (err_code) {
			std::cout << dos::error::messages[err_code] << std::endl;
		}

		return err_code;
	}

	/**
	* INT 21,43 - Get/Set File Attributes
	* AH = 43h
	* AL = 00 to get attribute
	*    = 01 to set attribute
	* DS:DX = pointer to an ASCIIZ path name
	* CX = attribute to set
	*
	* |5|4|3|2|1|0|  CX  valid file attributes
	*  | | | | | `---- 1 = read only
	*  | | | | `----- 1 = hidden
	*  | | | `------ 1 = system
	*  | `--------- not used for this call
	*  `---------- 1 = archive
	*
	* on return:
	* AX = error code if CF set  (see DOS ERROR CODES)
	* CX = the attribute if AL was 00
	*/
	file::attributes_t get_file_attributes(char* path_name) {
		file::attributes_t attributes;
		error_code_t err_code = 0;
		__asm {
			.8086
			push	ds
			pushf

			lds		dx, path_name
			xor		cx, cx
			xor		al, al						; AL = 00 to get attribute
			mov		ah, CHANGE_FILE_MODE
			int		DOS_SERVICE
			jnc		OK
			mov		err_code, ax
			xor		ax, ax
	OK:		mov		attributes, ax

	END:	popf
			pop		ds
		}

		if (err_code) {
			std::cout << dos::error::messages[err_code] << std::endl;
		}

		return attributes;
	}

	/**
	* @note DOSBOX does not allow
	* @see file::attributes_t get_file_attributes(char* path_name)
	*/
	error_code_t set_file_attributes(char* path_name, file::attributes_t attributes) {
		error_code_t err_code = 0;
		__asm {
			.8086
			push	ds
			pushf

			lds		dx, path_name
			mov		cx, attributes
			mov		al, 1					; AL = 01 to set attribute
			mov		ah, CHANGE_FILE_MODE
			int		DOS_SERVICE
			jnc		END
			mov		err_code, ax

	END:	popf
			pop		ds
		}

		if (err_code) {
			std::cout << dos::error::messages[err_code] << std::endl;
		}

		return err_code;
	}

}