/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.10.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef DOS_SERVICES_FILES_H
#define DOS_SERVICES_FILES_H

#include "dos_services_types.h"

namespace dos {

    // 36  Get disk free space
    void get_disk_free_space(uint8_t drive_number, file::disk_space_info_t* info);

    // 37  Get/set switch character (undocumented)
    // 38  Get/set country dependent information
    // 39  Create subdirectory (mkdir)
    // 3A  Remove subdirectory (rmdir)
    // 3B  Change current subdirectory (chdir) 
    // 
    // 3C  Create file using handle
    file::handle_t create_file_using_handle(char* path_name, uint16_t create_attributes = file::CREATE_READ_ONLY);

    // 3D  Open file using handle
    file::handle_t open_file_using_handle(char* path_name, uint8_t access_attributes = file::ACCESS_READ_ONLY);

    // 3E  Close file using handle
    // 3F  Read file or device using handle
    // 40  Write file or device using handle
    // 41  Delete file
    // 42  Move file pointer using handle
    // 43  Change file mode
    // 44  I/O control for devices (IOCTL)
    // 45  Duplicate file handle
    // 46  Force duplicate file handle
    // 47  Get current directory

}

#endif