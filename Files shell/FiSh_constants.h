#pragma once
#ifndef FISH_CONSTANTS_H
#define FISH_CONSTANTS_H

#include <filesystem>

namespace constants {

	const std::string defaultDirName = "File Shell(_FiSh_).ubFR8-fHlW3-YNEV0-BkxEO-8J0ld-BLRxu-26eX8-wcA9V-KI1cd-N12wl";
	const std::experimental::filesystem::v1::path temp_path = std::experimental::filesystem::temp_directory_path();

}

#endif