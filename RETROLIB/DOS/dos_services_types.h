/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef DOS_SERVICES_TYPES_H
#define DOS_SERVICES_TYPES_H

#include <stdint.h>

namespace dos {

	/**
	* DOS int 21h, 36h	Get Disk Free Space
	*/
	struct disk_space_info_t {

		int16_t sectors_per_cluster;	// 0FFFFH if the drive number is invalid
		int16_t available_clusters;
		int16_t bytes_per_sector;
		int16_t clusters_per_drive;

	};

}

#endif