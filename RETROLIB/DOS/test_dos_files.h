/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_DOS_FILES_H
#define TEST_DOS_FILES_H

#include "../TEST/debug_macros.h"

#include "dos_services_types.h"
#include "dos_services_files.h"

#include <stdio.h>

namespace test_dos_files {

	void run() {
		INFO("* test DOS Services Files");
		if (YESNO("* 141\ttest disk free space?")) {
			dos::file::disk_space_info_t info;
			dos::get_disk_free_space(0, &info);
			LOG(info.sectors_per_cluster);
			LOG(info.available_clusters);
			LOG(info.bytes_per_sector);
			LOG(info.clusters_per_drive);
			uint32_t total_size = info.bytes_per_sector;
			total_size *= info.sectors_per_cluster;
			total_size *= info.clusters_per_drive;
			uint32_t free_size = info.bytes_per_sector;
			free_size *= info.sectors_per_cluster;
			free_size *= info.available_clusters;
			LOG(free_size);
			LOG(total_size);
			// should error
			dos::get_disk_free_space(9, &info);
			LOG(info.sectors_per_cluster);
			LOG(info.available_clusters);
			LOG(info.bytes_per_sector);
			LOG(info.clusters_per_drive);
		}
		if (YESNO("* 142\ttest create file?")) {
			char fpath[13] = "";
			INFO("* file create error...");
			LOG(dos::create_file_using_handle(fpath)); // errors out
			printf("* Enter filename: ");
			scanf("%s", fpath);
			LOG(dos::create_file_using_handle(fpath, dos::file::CREATE_READ_ONLY | dos::file::CREATE_HIDDEN));
		}
		if (YESNO("* 143\ttest change mode?")) {
			char fpath[13] = "";
			INFO("* file mode error");
			LOG(dos::get_file_attributes(fpath)); // errors out
			printf("* Enter filename: ");
			scanf("%s", fpath);
			LOG(dos::get_file_attributes(fpath));
		}
		if (YESNO("* 144\ttest open file?")) {
			char fpath[13] = "";
			INFO("* file open error...");
			LOG(dos::open_file_using_handle(fpath)); // errors out
			printf("* Enter filename: ");
			scanf("%s", fpath);
			LOG(dos::open_file_using_handle(fpath, dos::file::ACCESS_READ_ONLY));
		}
		if (YESNO("* 145\ttest write file?")) {
		}
		if (YESNO("* 146\ttest read file?")) {
		}
		if (YESNO("* 147\ttest close file?")) {
		}
		if (YESNO("* 148\ttest delete file?")) {
		}
	}

}

#endif