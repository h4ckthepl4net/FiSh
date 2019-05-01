#include "pch.h"
#include "FiSh_utils.h"

namespace utils {

	std::string generateRandomName() {
		std::string name = "File Shell(_FiSh_).";
		for (int i = 1; i < 30; i++) {
			if (i && i % 6 == 0) {
				name += '-';
			}
			else {
				unsigned long long seed = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
				unsigned long long tmpSeed = seed;
				seed >>= 16;
				seed <<= 16;
				srand((tmpSeed ^ seed) << i);
				char num = 48 + (rand() % 10);
				char upperAlpha = 65 + (rand() % 26);
				char lowerAlpha = 97 + (rand() % 26);
				char randDecision = (unsigned char)rand() % 3;
				name += (char)((randDecision == 0) ? num : ((randDecision == 1) ? upperAlpha : lowerAlpha));
			}
		}
		return name;
	}

	bool askDecision(const char text[] = "Are you sure? (Y/N)") {
		std::string decision;
		do {
			std::cout << std::endl << text << std::endl;
			std::cin >> decision;
			if (decision == "Y" || decision == "y") {
				return true;
			}
			else if (decision == "N" || decision == "n") {
				return false;
			}
		} while (1);
	}

	std::vector<std::string> readCommand() {
		std::string tmp;
		do {
			std::getline(std::cin, tmp);
		} while (tmp.size() == 0);
		std::istringstream command(tmp);
		std::vector<std::string> result;
		while (command >> tmp) {
			result.push_back(tmp);
		}
		return result;
	}

	char getProgramTempDirectoryPath() {
		bool defaultCase = true;
#ifdef _WIN32
		HKEY key;
		if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FiSh", 0, KEY_ALL_ACCESS, &key) == ERROR_SUCCESS) {
			DWORD type = REG_SZ;
			std::string keyVal;
			char* keyRawVal = new char[49];
			DWORD buffSize = 49;
			if (RegQueryValueExA(key, "", NULL, &type, (LPBYTE)keyRawVal, &buffSize) == ERROR_SUCCESS && strlen(keyRawVal) > 28) {
				keyVal = keyRawVal;
				delete[] keyRawVal;
				if (!std::experimental::filesystem::exists(::temp_path.u8string() + keyVal)) {
					std::experimental::filesystem::create_directory(::temp_path.u8string() + keyVal);
				}
				defaultCase = false;
			}
			else {
				keyVal = keyRawVal;
				delete[] keyRawVal;
				keyVal = generateRandomName();
				if (RegSetValueExA(key, "", NULL, REG_SZ, (LPBYTE)keyVal.c_str(), 49) == ERROR_SUCCESS) {
					std::experimental::filesystem::create_directory(::temp_path.u8string() + keyVal);
					defaultCase = false;
				}
			}
		}
		else if (RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FiSh", NULL, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL) == ERROR_SUCCESS) {
			std::string newFolderName = generateRandomName();
			if (RegSetValueExA(key, "", NULL, REG_SZ, (LPBYTE)newFolderName.c_str(), 49) == ERROR_SUCCESS) {
				std::experimental::filesystem::create_directory(::temp_path.u8string() + newFolderName);
				defaultCase = false;
			}
		}
		RegCloseKey(key);
#endif
		if (defaultCase) {
			std::experimental::filesystem::create_directory(::temp_path.u8string() + ::defaultDirName);
		}
		return 0;
	}

}