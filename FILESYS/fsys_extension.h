/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef FSYS__EXTENSION_H
#define FSYS__EXTENSION_H

namespace fsys {

	/**
	*  @brief	Retrieve file extension, if there is one
	*  @param	file_path
	*  @retval  string file extension or empty string if not found
	*/
	const char* extension(const char* file_path) {
		const char* dot = strrchr(file_path, '.');
		if (!dot || dot == file_path) {
			return "";
		}
		else {
			return ++dot;
		}
	}

}

#endif
