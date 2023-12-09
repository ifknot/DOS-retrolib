/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_TOOLBOX_H
#define MEM_TOOLBOX_H

#include <iostream>
#include <stdint.h>

#include "mem_types.h"

#include "../DOS/dos_services_files_types.h"

namespace mem {

	/**
	* @brief Use DOS INT 21h, Function 48h, to determine the amount of memory available to a user's program.
	* @note By setting BX=FFFFh before calling, this function can be used to find the amount of
	* available memory, which will be returned in BX. (The call will return an error, which can be ignored,
	* since DOS cannot allocate more than 640k of memory.)
	*/
	uint32_t available_low_memory_bytes();

	/**
	* @brief convenience function dump memory to std::cout
	*/
	address_t dump(address_t start, uint32_t nbytes);

	/**
	* @brief dump formatted contents of memory to output stream
	* @note mimics the DOS DEBUG format of output
	*
	* @return address_t - the end address of the dumped memory
	*/
	// TODO:
	//address_t dump_large_ostream(std::ostream& os, const address_t start, const uint32_t nbytes); 

	/**
	* @brief dump full 64K page of memory to ostream
	*/
	//address_t dump_page_ostream(std::ostream& os, const address_t start)

	/**
	* @brief debug formatted dumps *upto* a page (64K) of memory to ostream
	*/
	address_t dump_ostream(std::ostream& os, address_t start, uint16_t nbytes);

	/**
	* @brief debug fromatted dumps a paragraph (16 bytes) of memory to ostream
	*/
	address_t dump_paragraph_ostream(std::ostream& os, address_t start);

	/**
	* @brief use DOS to load contents of a file to memory
	* @note loads raw bytes
	*
	* @return file::size_t - the actual byte count loaded
	*/
	// TODO
	//dos::file::size_t load_large_from_file(const char* path_name, address_t start, uint32_t bytes);

	//dos::file::size_t load_page_from_file(const char* path_name, address_t start);

	/**
	* @brief loads unformatted *upto* a page (64K bytes or 4096 paragraphs) of from file to memory
	* @note loads raw bytes
	*
	* @return file::size_t - the actual byte count loaded
	*/
	dos::file::size_t load_from_file(const char* path_name, address_t start, uint16_t nbytes);

	/**
	* @brief use DOS to save contents of memory to file
	* @note saves raw bytes
	*
	* @return file::size_t - the actual byte count saved
	*/
	// TODO
	//dos::file::size_t save_large_to_file(const char* path_name, address_t start, uint32_t bytes);

	//dos::file::size_t save_page_to_file(const char* path_name, address_t start);

	/**
	* @brief saves unformatted *upto* a page (64K bytes or 4096 paragraphs) of memory to file
	* @note saves raw bytes
	*
	* @return file::size_t - the actual byte count saved
	*/
	dos::file::size_t save_to_file(const char* path_name, address_t start, uint16_t nbytes);

	/**
	* @brief write contents of memory to output stream
	* @note the ostream will interpret control characters
	*
	* @return size_t - the actual number of bytes written
	*/
	// TODO
	//dos::file::size_t write_large_ostream(std::ostream& os, address_t start, uint32_t nbytes);

	/**
	* @brief write full 64K page of memory to ostream
	*/
	//dos::file::size_t write_page_ostream(std::ostream& os, address_t start);

	/**
	* @brief write *upto* a page (64K bytes or 4096 paragraphs) of memory to ostream
	* @note the ostream will interpret control characters
	*
	* @return size_t - the actual number of bytes written
	*/
	dos::file::size_t write_ostream(std::ostream& os, address_t start, uint16_t nbytes);

}

#endif