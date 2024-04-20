/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      20.04.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef KBD_CONSTANTS_H
#define KBD_CONSTANTS_H

#define MAX_SCAN_CODES 256
#define KEYBOARD_CONTROLLER_OUTPUT_BUFFER 0x60
#define KEYBOARD_CONTROLLER_STATUS_REGISTER 0x64
#define KEY_PRESSED 1
#define KEY_RELEASED 0
#define PIC_OPERATION_COMMAND_PORT 0x20
#define KEYBOARD_INTERRUPT_VECTOR 0x09

 /**
 * PPI stands for Programmable Peripheral Interface(which is the Intel 8255A chip)
 * The PPI ports are only for IBM PC and XT, however port A is mapped to the same
 *  I/O address as the Keyboard Controller's (Intel 8042 chip) output buffer for compatibility.
 */
#define PPI_PORT_A 0x60
#define PPI_PORT_B 0x61
#define PPI_PORT_C 0x62
#define PPI_COMMAND_REGISTER 0x63

#endif