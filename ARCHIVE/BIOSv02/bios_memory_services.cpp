#include "bios_memory_services.h"


#include "bios_memory_services_constants.h"

#include "../SYS/system_low_memory_constants.h"

namespace bios {

	uint16_t get_low_memory_size() {
		uint16_t kbytes = 0;
		__asm {
			.8086
			clc							; Clear carry flag
			int		REPORT_MEMORY_SIZE	; Switch to the BIOS(= request low memory size)
			jc		ERR					; The carry flag is set if it failed
			mov		kbytes, ax
	ERR:		
		}
		return kbytes;
	}

	/**
	* Normally, the "Extended BIOS Data Area" (EBDA) is located at the segment stored at 0x0040:0x000E,
	* but this is only true for EISA and MCA systems (at least that's what I found in various specs).
	* On older systems, the word at 0x040E is "LPT 4 port address"
	* whilst on PS/2 systems it is indeed the EBDA segment.
	*/
	uint16_t get_ebda_segment() {
		uint16_t ebda;
		__asm {
			.8086
			mov		ax, RAM_SEGMENT_BDA
			mov		es, ax
			mov		ax, [es:PORT_ADDRESS_LPT4]	; get the segment of the EBDA
			mov		ebda, ax
		}
		return ebda;
	}

	/**
	* Only valid if an EBDA is present 
	*/
	uint16_t get_ebda_size() {
		uint16_t size = 0;
		__asm {
			.8086
			mov		ax, RAM_SEGMENT_BDA
			mov		es, ax
			mov		ax, [es:PORT_ADDRESS_LPT4]	; get the segment of the EBDA
			mov		es, ax						; es now points to EBDA
			mov		al, [es:0h]					; number of bytes allocated to EBDA in Kbytes
			xor		ah, ah
			mov		size, ax
		}
		return size;
	}

}
