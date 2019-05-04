#pragma once
#ifndef FISH_CONSTANTS_H
#define FISH_CONSTANTS_H

#include <filesystem>
#include <string>

namespace constants {

	extern const std::string defaultDirName;
	extern const std::experimental::filesystem::v1::path temp_path;
	extern std::string temp_directory_name;

}

#endif