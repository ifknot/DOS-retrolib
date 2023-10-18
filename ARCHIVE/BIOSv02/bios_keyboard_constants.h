/**
 *
 *  @brief     
 *  @url https://www.stanislavs.org/helppc/int_16.html
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef BIOS_KEYBOARD_CONSTANTS_H
#define BIOS_KEYBOARD_CONSTANTS_H

#include <stdint.h> // Open Watcom fails with <cstdint>

#define BIOS_KEYBOARD_SERVICE	16h

#define WAIT_FOR_KEYSTROKE_AND_READ 0
#define GET_KEYSTROKE_STATUS		1
#define GET_SHIFT_STATUS			2

 // available only on AT and later machines that support the extended keyboard BIOS
#define AT_SET_KEYBOARD_TYPEMATIC_RATE	3	
#define AT_KEYBOARD_CLICK_ADJUSTMENT	4
#define AT_KEYBOARD_BUFFER_WRITE		5
#define AT_WAIT_FOR_KEYSTROKEAND_READ	10
#define AT_GET_KEYSTROKE_STATUS			11
#define AT_GET_SHIFT_STATUS				12

#endif