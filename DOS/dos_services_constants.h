/*****************************************************************//**
 * \file   dos_services_constants.h
 * \brief  
 * 
 * \author ifkno
 * \date   October 2021
 *********************************************************************/
//#pragma once
#ifndef DOS_SERVICES_CONSTANTS_H
#define DOS_SERVICES_CONSTANTS_H

#define DOS_SERVICE 0x21

namespace dos {

	enum service_t {
		PROGRAM_TERMINATE = 0,
		KEYBOARD_INPUT_WITH_ECHO,
		DISPLAY_OUTPUT,
		WAIT_FOR_AUXILIARY_DEVICE_INPUT,
		AUXILIARY_OUTPUT,
		PRINTER_OUTPUT,
		DIRECT_CONSOLE_IO,
		WAIT_FOR_DIRECT_CONSOLE_INPUT_WITHOUT_ECHO,
		WAIT_FOR_CONSOLE_INPUT_WITHOUT_ECHO,
		PRINT_STRING,
		BUFFERED_KEYBOARD_INPUT,
		CHECK_STANDARD_INPUT_STATUS,
		CLEAR_KEYBOARD_BUFFER, 
		DISK_RESET,
		SELECT_DISK,
		OPEN_FILE_USING_FCB,
		CLOSE_FILE_USING_FCB,
		SEARCH_FOR_FIRST_ENTRY_USING_FCB,
		SEARCH_FOR_NEXT_ENTRY_USING_FCB,
		DELETE_FILE_USING_FCB,
		SEQUENTIAL_READ_USING_FCB,
		SEQUENTIAL_WRITE_USING_FCB,
		CREATEFILE_USING_FCB,
		RENAME_FILE_USING_FCB,
		DOS_DUMMY_FUNCTION_1,							// CP/M_NOT_USED/LISTED
		GET_CURRENT_DEFAULT_DRIVE,
		SET_DISK_TRANSFER_ADDRESS,
		GET_ALLOCATION_TABLE_INFORMATION,
		GET_ALLOCATION_TABLE_INFO_FOR_SPECIFIC_DEVICE,
		DOS_DUMMY_FUNCTION_2,							// CP/M_NOT_USED/LISTED
		DOS_DUMMY_FUNCTION_3,							// CP/M_NOT_USED/LISTED
		GET_POINTER_TO_DEFAULT_DRIVE_PARAMETER_TABLE,	// UNDOCUMENTED
		DOS_DUMMY_FUNCTION_4,							// CP/M_NOT_USED/LISTED
		RANDOM_READ_USING_FCB,
		RANDOM_WRITE_USING_FCB,
		GET_FILE_SIZE_USING_FCB,
		SET_RELATIVE_RECORD_FIELD_FOR_FCB,
		SET_INTERRUPT_VECTOR,
		CREATE_NEW_PROGRAM_SEGMENT,
		RANDOM_BLOCK_READ_USING_FCB,
		RANDOM_BLOCK_WRITE_USING_FCB,
		PARSE_FILENAME_FOR_FCB,
		GET_DATE,
		SET_DATE,
		GET_TIME,
		SET_TIME,
		TOGGLE_VERIFY_SWITCH,
		GET_DISK_TRANSFER_ADDRESS,
		GET_DOS_VERSION_NUMBER,
		TERMINATE_PROCESS_AND_REMAIN_RESIDENT,
		GET_POINTER_TO_DRIVE_PARAMETER_TABLE,			// UNDOCUMENTED
		GET_SET_CTRL,									
		GET_ADDRESS_TO_DOS_CRITICAL_FLAG,				// UNDOCUMENTED
		GET_INTERRUPT_VECTOR,
		GET_DISK_FREE_SPACE,
		GET_SET_SWITCH_CHARACTER,						// UNDOCUMENTED
		GET_SET_COUNTRY_DEPENDENT_INFORMATION,
		CREATE_SUBDIRECTORY,				
		REMOVE_SUBDIRECTORY,
		CHANGE_CURRENT_SUBDIRECTORY,
		CREATE_FILE_USING_HANDLE,
		OPEN_FILE_USING_HANDLE,
		CLOSE_FILE_USING_HANDLE,
		READ_FILE_OR_DEVICE_USING_HANDLE,
		WRITE_FILE_OR_DEVICE_USING_HANDLE,
		DELETE_FILE,
		MOVE_FILE_POINTER_USING_HANDLE,
		CHANGE_FILE_MODE,
		IO_CONTROL_FOR_DEVICES,
		DUPLICATE_FILE_HANDLE,
		FORCE_DUPLICATE_FILE_HANDLE,
		GET_CURRENT_DIRECTORY,
		ALLOCATE_MEMORY_BLOCKS,
		FREE_ALLOCATED_MEMORY_BLOCKS,
		MODIFY_ALLOCATED_MEMORY_BLOCKS,
		EXEC_LOAD_AND_EXECUTE_PROGRAM,
		TERMINATE_PROCESS_WITH_RETURN_CODE,
		GET_RETURN_CODE_OF_SUB_PROCESS,
		FIND_FIRST_MATCHING_FILE,
		FIND_NEXT_MATCHING_FILE,
		SET_CURRENT_PROCESS_ID,							// UNDOCUMENTED
		GET_CURRENT_PROCESS_ID,							// UNDOCUMENTED
		GET_POINTER_TO_DOS_INVARS,						// UNDOCUMENTED
		GENERATE_DRIVE_PARAMETER_TABLE,					// UNDOCUMENTED
		GET_VERIFY_SETTING,
		CREATE_PSP,										// UNDOCUMENTED
		RENAME_FILE,
		GET_SET_FILE_DATE_AND_TIME_USING_HANDLE,
		GET_SET_MEMORY_ALLOCATION_STRATEGY,				// 3.X + , _UNDOCUMENTED
		GET_EXTENDED_ERROR_INFORMATION,					// 3.X + 
		CREATE_TEMPORARY_FILE,							// 3.X + 
		CREATE_NEW_FILE,								// 3.X + 
		LOCK_UNLOCK_FILE_ACCESS,						// 3.X + 
		CRITICAL_ERROR_INFORMATION,						// UNDOCUMENTED
		NETWORK_SERVICES,								// 3.1 + 
		NETWORK_REDIRECTION,							// 3.1 + 
		GET_FULLY_QUALIFIED_FILE_NAME,					// UNDOCUMENTED
		GET_ADDRESS_OF_PROGRAM_SEGMENT_PREFIX,			// 3.X + 
		GET_SYSTEM_LEAD_BYTE_TABLE,						// MSDOS_2.25_ONLY
		SET_DEVICE_DRIVER_LOOK_AHEAD,					// UNDOCUMENTED
		GET_EXTENDED_COUNTRY_INFORMATION,				// 3.3 + 
		GET_SET_GLOBAL_CODE_PAGE,						// 3.3 + 
		SET_HANDLE_COUNT,								// 3.3 + 
		FLUSH_BUFFER,									// 3.3 + 
		GET_SET_DISK_SERIAL_NUMBER						// UNDOCUMENTED
	};

}

#endif