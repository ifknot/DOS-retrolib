/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef SYSTEM_UPPER_MEMORY_CONSTANTS_H
#define SYSTEM_UPPER_MEMORY_CONSTANTS_H

// 'upper' memory area (UMA)
// 8K slot available for user programs
#define ROM_SEGMENT_USER	0F400h
// 40K BASIC in ROM
#define ROM_SEGMENT_BASIC	0F600h
// BIOS code in ROM
#define ROM_SEGMENT_BIOS	0FE00h

#endif