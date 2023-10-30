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

namespace test_dos_files {

	void run() {
		INFO("* test DOS Services Files");
		dos::disk_space_info_t info;
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
	}

}

#endif