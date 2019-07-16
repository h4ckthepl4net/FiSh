#pragma once
#ifndef FISH_CONSTANTS_H
#define FISH_CONSTANTS_H

#include <filesystem>
#include <string>

namespace constants {

	extern const std::string defaultDirName;
	extern const std::experimental::filesystem::v1::path temp_path;
	extern std::string temp_directory_name;

	enum passwordIsSet {
		PASS_N_SET = 0, //Password is not set
		PASS_SET = 1, //Password is set
		REG_KEY_E_PASS_FILE_N_E = 2, //Registry key exists, password file not exists
		REG_KEY_N_E_PASS_FILE_E = 3, //Registry key not exists, password file exists
	};

}

#endif