/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      22.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_AVAILABLE_LOW_MEMORY_H
#define MEM_AVAILABLE_LOW_MEMORY_H

#include <stdint.h>

namespace mem {

	/**
	* @brief Use DOS INT 21h, Function 48h, to determine the amount of memory available to a user's program.
	* @note By setting BX=FFFFh before calling, this function can be used to find the amount of 
    * available memory, which will be returned in BX. (The call will return an error, which can be ignored,
	* since DOS cannot allocate more than 640k of memory.)
	*/
	uint32_t available_low_memory();

}

#endif