/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef DOS_SERVICES_TYPES_H
#define DOS_SERVICES_TYPES_H

#include <stdint.h>

namespace dos {

	namespace file {

		typedef uint16_t handle_t;

		/**
		* Bitfields for file attributes:
		* 
		* 0	read-only
		* 1	hidden
		* 2	system
		* 3	volume label (ignored)
		* 4	reserved, must be zero (directory)
		* 5	archive bit
		* 7	if set, file is shareable under Novell NetWare
		*/
		enum attributes {
			READ_WRITE = 0,
			READ_ONLY,
			HIDDEN,
			SYSTEM = 4,
			VOLUME = 8,
			ARCHIVE = 32,
			SHAREABLE = 128,
		};

		/**
		* DOS int 21h, 36h	Get Disk Free Space
		*/
		struct disk_space_info_t {

			int16_t sectors_per_cluster;	// 0FFFFH if the drive number is invalid
			int16_t available_clusters;
			int16_t bytes_per_sector;
			int16_t clusters_per_drive;

		};

	}

	/**
	* Offset Size		Description
	*	00   byte		'M' 4Dh  member of a MCB chain, (not last)
	*					'Z' 5Ah  indicates last entry in MCB chain
	*					other values cause "Memory Allocation Failure" on exit
	*	01   word		PSP segment address of MCB owner (Process Id)
	*					possible values:
	*						0 = free
	*						8 = Allocated by DOS before first user pgm loaded
	*						other = Process Id/PSP segment address of owner
	*	03   word		number of paras related to this MCB (excluding MCB)
	*	05	3bytes		reserved
	*	08  8bytes		ASCII program name, NULL terminated if less than max length (DOS 4.x+)
	*	10  nbytes	first byte of actual allocated memory block
	*
	* @note  An undocumented way to find the first or 'base' MemBlockRec to use DOS Fn 52H.
	*/
	struct mcb_t {

		uint8_t		signature;		// 'M' (4dH)=valid; 'Z'(5aH)=last block in list
		uint16_t	owner_id;		// segment address of PSP of owner (0=owns self)
		uint16_t	size_paras;		// allocation size in 16-byte paragraphs
		uint8_t		reserved[3];
		char		owner_name[8];	// 7 or fewer bytes, followed by 00H.  When DOS loads a program, this field is filled - Prior to DOS 4.0, this field contained garbage

	};

}

#endif