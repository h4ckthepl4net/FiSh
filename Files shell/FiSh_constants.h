#pragma once
#ifndef FISH_CONSTANTS_H
#define FISH_CONSTANTS_H

#include <filesystem>
#include <string>

namespace constants {

	extern const std::string defaultDirName;
	extern const std::experimental::filesystem::v1::path temp_path;
	extern std::string temp_directory_name;

	enum PasswordIsSet {
		PASS_N_SET, //Password is not set
		PASS_SET, //Password is set
		REG_KEY_E_PASS_FILE_N_E, //Registry key exists, password file not exists
		REG_KEY_N_E_PASS_FILE_E, //Registry key not exists, password file exists
	};

	enum RootOperationType {
		NO_OPERATION, //No any operation
		SET_ROOT_PASS, //Set root mode password
		DEL_ROOT_PASS, //Delete root mode password
		ON_ROOT_MODE, //Turn root mode on
		OFF_ROOT_MODE, //Turn root mode off
	};

}

#endif