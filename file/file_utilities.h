/**
 *
 *  @file      file_utilities.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef FILE_UTILITIES
#define FILE_UTILITIES

#include <string>

namespace jtl {

	namespace filesystem {

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

}

#endif