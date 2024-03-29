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


/** @url http://vitaly_filatov.tripod.com/ng/asm/asm_001.10.html
INT 12h (18)             Report Memory Size
 
    Reports the number of contiguous 1K memory blocks in the system (up to
    640K).
 
       On entry:      No parameters
 
       Returns:       AX         Memory size (up to 640K)
 
  --------------------------------------------------------------------------
 
       Notes:         This service determines memory by either examining
                      the DIP switches on the system board or using the
                      value stored in the CMOS battery, depending on the
                      type of machine.
 
                      The value returned in AX is the same as that stored
                      at memory location 0:0413h, which is initialized
                      during the power-up tests.
 
                      This is the amount of memory available to the entire
                      system. This is not the amount of memory available
                      to the user's program. Use INT 21h, Function 48h, to
                      determine the amount of memory available to a user's
                      program.
 
                      To determine the amount of memory above the 1024K
                      address range, use INT 15h, Service 88h.
 
                      If the CMOS battery memory value or the DIP switch
                      value is greater than the actual amount of memory,
                      then the actual amount of memory is returned by this
                      interrupt.

*/
#define REPORT_MEMORY_SIZE 12h

/** @url http://vitaly_filatov.tripod.com/ng/asm/asm_010.88.html
Function 48h (72)        Allocate Memory
 
    Allocates a specified number of memory paragraphs.
 
       On entry:      AH         48h
                      BX         Number of memory paragraphs to be allocated
 
       Returns:       AX         Segment address of allocated memory
                                 Error code, if CF is set
                      BX         Size of largest available block (CF set)
 
       Error codes:   7          Memory control blocks destroyed
                      8          Insufficient memory
 
                      Call Function 59h for extended error code information
                      (DOS 3.0 and above).
 
  --------------------------------------------------------------------------
 
    Function 48h dynamically allocates memory, in multiples of 16 bytes
    (one paragraph). The amount of memory to be allocated, in paragraphs,
    is specified in BX. If the function is successful, AX:0000 points to
    the allocated memory block. (AX holds the segment address; the offset
    is always 0000).
 
       Notes:         By setting BX=FFFFh before calling, this function
                      can be used to find the amount of **available memory**,
                      which will be returned in BX. (The call will return
                      an error, which can be ignored, since DOS cannot
                      allocate more than 640k of memory.)

*/
#define ALLOCATE_REPORT_MEMORY   48h

/**
INT 15h,  88h (136)      Get extended memory size                  XT-286, AT
 
    Reports amount of memory above 1024K.
 
       On entry:      AH         88h
 
       Returns:       Carry      Set if error, else cleared
                      AX         Number of 1K blocks above 1024K
 
  --------------------------------------------------------------------------
 
       Notes:         This service is available only for the AT and XT-
                      286.
 
                      The amount of memory returned by this service is
                      stored in the CMOS battery. It is determined and set
                      during power-on.
 
                      For the memory above the 1024K range to be usable,
                      the planar memory (memory on the system board) must
                      be fully populated. The memory above the 1024K range
                      is often called "extended" memory.

*/
// int 15h SYSTEM_BIOS_SERVICES in bios_global_constants
#define GET_EXTENDED_MEMORY_SIZE 88h





#endif
