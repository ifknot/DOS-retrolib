/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef SYSTEM_CONVENTIONAL_MEMORY_CONSTANTS_H
#define SYSTEM_CONVENTIONAL_MEMORY_CONSTANTS_H

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

#endif