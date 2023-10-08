/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef SYSTEM_LOW_MEMORY_CONSTANTS_H
#define SYSTEM_LOW_MEMORY_CONSTANTS_H

 // BIOS memory constants:
 // 'low' memory area
 // BIOS interrupt vectors (first 1K)
#define RAM_INTERRUPT_VECTORS 0h
// 00:00 256 dwords Interrupt vector table
// 30:00 256 bytes	Stack area used during post and bootstrap
// BIOS data area (BDA) 256 bytes
#define RAM_SEGMENT_BDA		40h
// DOS & BASIC RAM area
#define RAM_SEGMENT_DOS		50h
// I/O drivers from IO.SYS/IBMBIO.COM
#define RAM_SEGMENT_IO_SYS	50h
// LPT4 port address (except PS/2 Extended BIOS Data Area segment EBDA)
#define PORT_ADDRESS_LPT4	0Eh

#endif