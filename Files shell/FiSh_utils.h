#pragma once
#ifndef FISH_UTILS
#define FISH_UTILS

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#include <winreg.h>
#endif // __WIN32

#include "FiSh_constants.h"

namespace utils {

	std::string generateRandomName();

	bool askDecision(const char[]);

	std::vector<std::string> readCommand();

	char getProgramTempDirectoryPath();

}

#endif

