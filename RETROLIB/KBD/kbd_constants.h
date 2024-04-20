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
#define PIC_OPERATION_COMMAND_PORT 20h

 /**
 * PPI stands for Programmable Peripheral Interface(which is the Intel 8255A chip)
 * The PPI ports are only for IBM PC and XT, however port A is mapped to the same
 *  I/O address as the Keyboard Controller's (Intel 8042 chip) output buffer for compatibility.
 */
#define PPI_PORT_A 60h
#define PPI_PORT_B 61h
#define PPI_PORT_C 62h
#define PPI_COMMAND_REGISTER 63h

#endif