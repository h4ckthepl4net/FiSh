#pragma once
#ifndef FISH_UTILS_H
#define FISH_UTILS_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <filesystem>
#include <conio.h>

#ifdef _WIN32
#include <windows.h>
#include <winreg.h>
#endif // __WIN32

#include "FiSh_constants.h"

namespace utils {

	std::string generateRandomName();
	char getProgramTempDirectoryPath();
	
	std::vector<std::string> readCommand();
	bool askDecision(const char[]);
	
	bool checkIfPasswordIsSet();
	char requestPassword(bool);

}

#endif

