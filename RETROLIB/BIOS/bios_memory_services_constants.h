/*****************************************************************//**
 * \file   bios_memory_services_constants.h
 * \brief  
 * 
 * \author ifkno
 * \date   November 2021
 *********************************************************************/
//#pragma once

#ifndef BIOS_MEMORY_SERVICES_CONSTANTS_H
#define BIOS_MEMORY_SERVICES_CONSTANTS_H

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
// Conventional Memroy
#define RAM_SEGMENT_USER	7B0h
#define RAM_SEGMENT_64K		1000h
#define RAM_SEGMENT_256K	4000h
#define RAM_SEGMENT_512K	8000h
#define RAM_SEGMENT_640K	0A000h
// reserved for all forms of video display
#define RAM_SEGMENT_VIDEO	0A400h
// memory expansion area 
#define RAM_SEGMENT_EXP		0C000h

#define IV_TABLE_SIZE		1024
#define BDA_SIZE			256	
// LPT4 port address (except PS/2 Extended BIOS Data Area segment EBDA)
#define PORT_ADDRESS_LPT4	0Eh

// 'upper' memory area (UMA)
// 8K slot available for user programs
#define ROM_SEGMENT_USER	0F400h
// 40K BASIC in ROM
#define ROM_SEGMENT_BASIC	0F600h
// BIOS code in ROM
#define ROM_SEGMENT_BIOS	0FE00h



#endif