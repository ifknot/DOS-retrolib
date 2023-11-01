/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_SAVE_FILE_H
#define MEM_SAVE_FILE_H

namespace mem {

	/**
	* @brief use DOS (3.x+) to save contents of memory to file 
	* @note saves raw bytes
	*
	* @return file::size_t - the actual byte count saved
	*/
	// TODO
	//dos::file::size_t save_file(char* path_name, const address_t start, const uint32_t bytes);

	/**
	* @brief saves unformatted *upto* a page (64K bytes or 4096 paragraphs) of memory to file
	* @note saves raw bytes
	*
	* @return file::size_t - the actual byte count saved
	*/
	// TODO
	//dos::file::size_t save_page_file(dos::file::handle_t fhandle, const address_t start, cont uint16_t bytes);

}

#endif