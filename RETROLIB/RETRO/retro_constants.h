/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      24.06.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef RETRO_CONSTANTS_H
#define RETRO_CONSTANTS_H

/**
* A paragraph is 16 bytes. Intel made the paragraph size of the x86 16 bytes, or four bits of the physical address.
* (Whether this decision was architectural based on programming paradigms of the time or a simple engineering expediency is debated)
* It's relevant primarily (if not exclusively) in x86 real mode, 
* being the distance between two addresses when increment/decrement a *segment* register by one.
*/
#define PARAGRAPH_SIZE 16	

#endif