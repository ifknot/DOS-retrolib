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
	* @brief save (unformatted) contents of memory to file - defaults to 256 bytes
	* @note mimics the DOS DEBUG program layout
	*
	* @return size_t - the end address of the paragraph
	*/
	//dos::file::size_t save_file(char* path_name, , const address_t start, const uint32_t bytes = 256);

	/**
	* @brief saves unformatted *upto* a page (64K bytes or 4096 paragraphs) of memory to file
	* @
	*/
	//dos::file::size_t save_page_file(dos::file::handle_t fhandle, const address_t start);

}

#endif