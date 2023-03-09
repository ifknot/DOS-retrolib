/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef FILE_EXTENSION_H
#define FILE_EXTENSION_H

#include <string>

namespace filesys {

	/**
	*  @brief	Retrieve file extension, if there is one
	*  @note	Uses std::string reverse find
	*  @param	file_path
	*  @retval  string file extension or empty string if not found
	*/
	std::string extension(std::string file_path) {
		std::string::size_type i = file_path.rfind('.');
		if (i != std::string::npos) {
			return file_path.substr(i + 1);
		}
		else {
			return "";
		}
	}

}

#endif
