/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_FILE_H
#define TEST_FILE_H

#include "../TEST/debug_macros.h"
#include "../DOS/dos_services_files.h"

#include "file.h"

namespace test_file {

	void run() {
		INFO("* testing file:: utilities...");
		if (YESNO("* 501\ttest get file extension?")) {
			char fpath[] = "testing.dat";
			LOG(file::get_extension(fpath));
		}
		if (YESNO("* 502\ttest get file size?")) {
			char fpath[] = "testing.dat";
			LOG(file::get_size(fpath)); // error displayed
			LOG(dos::create_file_using_handle(fpath, dos::file::CREATE_READ_WRITE));
			LOG(file::get_size(fpath));
			LOG(dos::delete_file(fpath));
			LOG(file::get_size("main.cpp"));
		}

	}

}

#endif