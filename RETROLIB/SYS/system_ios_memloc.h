/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef SYSTEM_IOS_MEMLOC_H
#define SYSTEM_IOS_MEMLOC_H

namespace sys {

	template<typename T>
	T read_memloc(uint32_t addr) {
		return *((T*)addr);
	}

	template<typename T>
	void write_memloc(T value, uint32_t addr) {
		return (T*)addr = value;
	}

}

#endif