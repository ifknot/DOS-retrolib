/**
 *
 *  @brief     INT 15H: AT Extended Services / APM
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.08.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef BIOS_CONFIG_SERVIES_CONSTANTS_H
#define BIOS_CONFIG_SERVIES_CONSTANTS_H

#define AT_EXTENDED_SERVICES			15H

#define KEYBOARD_INTERCEPT				4FH  
#define DEVICE_OPEN						80H  
#define DEVICE_CLOSE					81H  
#define PROGRAM_TERMINATION				82H  
#define SET_EVENT_WAIT_INTERVAL			8300H
#define CANCEL_EVENT_WAIT_INTERVAL		8301H
#define JOYSTICK_SUPPORT				84H  
#define SYSREQ_KEY						85H  
#define WAIT							86H  
#define MOVE_MEMORY_BLOCK				87H  
#define GET_EXTENDED_MEMORY_SIZE		88H  
#define SWITCH_TO_PROTECTED_MODE		89H  
#define DEVICE_BUSY						90H  
#define INTERRUPT_FINISHED				91H  
#define GET_SYSTEM_PARAMETERS			0C0H 


/**
* BiosSysParmsRec features bits:
*               ┌7┬6┬5┬4┬3┬2┬1┬0┐
*               │ │ │ │ │ │ │ │0│
*               └╥┴╥┴╥┴╥┴╥┴╥┴╥┴-┘ bit  mask
*               ║ ║ ║ ║ ║ ║ ║ ╚══► 0: 01H  (reserved)
*                ║ ║ ║ ║ ║ ║ ╚════► 1: 02H  0=PC-type I/O channel
*                ║ ║ ║ ║ ║ ╚══════► 2: 04H  1=Extended BIOS area allocated
*                ║ ║ ║ ║ ╚════════► 3: 08H  1=wait for ext event supported
*                ║ ║ ║ ╚══════════► 4: 10H  1=INT 15H 4fH supported by INT 09H
*                ║ ║ ╚════════════► 5: 20H  1=real-time clock is present
*                ║ ╚══════════════► 6: 40H  second interrupt chip is present
*                ╚════════════════► 7: 80H  hard disk BIOS uses DMA chnl 3
*/
#define RESERVED 							0x01
#define PC_TYPE_IO_CHANNEL 					0x02
#define EXTENDED_BIOS_AREA_ALLOCATED 		0x04
#define WAIT_FOR_EXT_EVENT_SUPPORTED 		0x08
#define INT_15H_4FH_SUPPORTED_BY_INT_09H 	0x10
#define REAL_TIME_CLOCK_IS_PRESENT 			0x20
#define SECOND_INTERRUPT_CHIP_IS_PRESENT 	0x40
#define HARD_DISK_BIOS_USES_DMA_CHNL_3 		0x80

namespace bios {

	namespace ext {

		/**
		* BiosSysParmsRec
		*   Offset Size Contents
		*   ▀▀▀▀▀▀ ▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
		*    +0      2  wLen       length of this table, in bytes
		*    +2      1  yModel     PC=ff,XT=fe or fb, PCjr=fd, AT=fc, unknown=ff
		*    +3      1  ySubModel  PC,XT,PCjr,AT=00; AT=01, XT-286=02
		*    +4      1  yRevLvl    BIOS revision level (0=initial release)
 		*    +5      1  rFeatures1 features bits:
		*               ┌7┬6┬5┬4┬3┬2┬1┬0┐
		*               │ │ │ │ │ │ │ │0│
		*               └╥┴╥┴╥┴╥┴╥┴╥┴╥┴-┘ bit  mask
 		*               ║ ║ ║ ║ ║ ║ ║ ╚══► 0: 01H  (reserved)
		*                ║ ║ ║ ║ ║ ║ ╚════► 1: 02H  0=PC-type I/O channel
		*                ║ ║ ║ ║ ║ ╚══════► 2: 04H  1=Extended BIOS area allocated
		*                ║ ║ ║ ║ ╚════════► 3: 08H  1=wait for ext event supported
		*                ║ ║ ║ ╚══════════► 4: 10H  1=INT 15H 4fH supported by INT 09H
		*                ║ ║ ╚════════════► 5: 20H  1=real-time clock is present
		*                ║ ╚══════════════► 6: 40H  second interrupt chip is present
		*                ╚════════════════► 7: 80H  hard disk BIOS uses DMA chnl 3
		*
		*    +6      1  rFeatures2 (reserved)
		*    +7      1  rFeatures3 (reserved)
		*    +8      1  rFeatures4 (reserved)
		*    +9      1  rFeatures5 (reserved)
		*           10             size of this structure
		*/
		struct bios_sys_parms_rec_t {
			uint16_t len;
			uint8_t model;
			uint8_t sub_model;
			uint8_t rev_level;
			uint8_t features;
		};

		// PC=ff, XT=fe or fb, PCjr=fd, AT=fc, unknown=ff 
		static char config_models[5][5] = {
			"XT",
			"AT",
			"PCjr",
			"XT",
			"PC"
		};

		// PC,XT,PCjr,AT=00; AT=01, XT-286=02
		static char config_sub_models[5][14] = {
			"PC,XT,PCjr,AT",
			"AT",
			"XT-286"
		};

	}

}

#endif