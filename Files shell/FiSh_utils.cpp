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
	std::string getCurrentDir() {
		//TODO: check for registry key
		char buffer[FILENAME_MAX];
		GetCurrentDirectoryA(FILENAME_MAX, buffer);
		return std::string(buffer) + "\\files directory"; // TODO: delete constant string from return statement
	}
	char getProgramTempDirectoryPath() {
		bool defaultCase = true;
#ifdef _WIN32
		HKEY key;
		if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FiSh", 0, KEY_QUERY_VALUE, &key) == ERROR_SUCCESS) {
			DWORD type = REG_SZ;
			char* keyRawVal = new char[49];
			DWORD buffSize = 49;
			if (RegQueryValueExA(key, "", NULL, &type, (LPBYTE)keyRawVal, &buffSize) == ERROR_SUCCESS && strlen(keyRawVal) > 28) {
				constants::temp_directory_name = keyRawVal;
				delete[] keyRawVal;
				if (!std::experimental::filesystem::exists(constants::temp_path.u8string() + constants::temp_directory_name)) {
					std::experimental::filesystem::create_directory(constants::temp_path.u8string() + constants::temp_directory_name);
				}
				defaultCase = false;
			}
			else {
				delete[] keyRawVal;
				constants::temp_directory_name = generateRandomName();
				if (RegSetValueExA(key, "", NULL, REG_SZ, (LPBYTE)constants::temp_directory_name.c_str(), 49) == ERROR_SUCCESS) {
					std::experimental::filesystem::create_directory(constants::temp_path.u8string() + constants::temp_directory_name);
					defaultCase = false;
				}
			}
		}
		else if (RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FiSh", NULL, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL) == ERROR_SUCCESS) {
			constants::temp_directory_name = generateRandomName();
			if (RegSetValueExA(key, "", NULL, REG_SZ, (LPBYTE)constants::temp_directory_name.c_str(), 49) == ERROR_SUCCESS) {
				std::experimental::filesystem::create_directory(constants::temp_path.u8string() + constants::temp_directory_name);
				defaultCase = false;
			}
		}
		RegCloseKey(key);
#endif
		if (defaultCase) {
			constants::temp_directory_name = constants::default_dir_name;
			std::experimental::filesystem::create_directory(constants::temp_path.u8string() + constants::default_dir_name);
		}
		return 0;
	}
	std::vector<std::string> getPathByParts(std::experimental::filesystem::path path) {
		std::vector<std::string> pathByParts;
		for (auto& part : path) {
			std::string partStr = part.u8string();
			if (partStr == ".." &&
				((path.is_relative() && pathByParts.size() > 0) ||
				(path.is_absolute() && pathByParts.size() > 2)) &&
				pathByParts.back() != "..") {
				pathByParts.erase(pathByParts.end() - 1);
			}
			else if (partStr != ".") {
				pathByParts.push_back(partStr);
			}
		}
		return pathByParts;
	};
	bool isInWorkingDirectory(std::experimental::filesystem::path path) {
		std::vector<std::string> currentPathByParts = utils::getPathByParts(utils::getCurrentDir());
		std::vector<std::string> pathByParts = utils::getPathByParts(path);
		for (int i = 0, length = currentPathByParts.size(); i < length; i++) {
			if (currentPathByParts[i] != pathByParts[i])
				return false;
		}
		return true;
	}

	std::vector<std::string> readCommand() {
		std::string tmp;
		do {
			std::getline(std::cin, tmp);
		} while (tmp.size() == 0);
		std::istringstream command(tmp);
		std::vector<std::string> result;
		while (command >> tmp) {
			if (tmp.find('"') != std::string::npos) {
				bool doubleQuoteFlag;
				char nextChar = command.get();
				if (nextChar != EOF) {
					do {
						doubleQuoteFlag = std::count(tmp.begin(), tmp.end(), '"') % 2;
						if (nextChar == '"')
							doubleQuoteFlag ^= 1;
						tmp += nextChar;
						nextChar = command.get();
						doubleQuoteFlag = nextChar != EOF;
					} while ((doubleQuoteFlag || nextChar != ' ') && nextChar != EOF);
				}
			}
			result.push_back(tmp);
		}
		return result;
	}
	bool askDecision(const char text[]) {
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

	void printPseudoPass(unsigned short length, char chrToPrint) {
		for (int i = 0; i < length; i++) {
			std::cout << chrToPrint;
		}
	}
	constants::PasswordIsSet checkIfPasswordIsSet() {
		bool defaultConditions = false;
#ifdef _WIN32
		HKEY key;
		if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FiSh\\isPassSet", 0, KEY_QUERY_VALUE, &key) == ERROR_SUCCESS) {
			defaultConditions = true;
		}
		RegCloseKey(key);
#endif
		if (std::experimental::filesystem::exists(constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::default_dir_name + "\\.password")) {
			return (defaultConditions) ? constants::PasswordIsSet::PASS_SET : constants::PasswordIsSet::REG_KEY_N_E_PASS_FILE_E;
		}
		else {
			return (defaultConditions) ? constants::PasswordIsSet::REG_KEY_E_PASS_FILE_N_E : constants::PasswordIsSet::PASS_N_SET;
		}
	}
	std::pair<std::string, unsigned char> requestPassword(bool settingPassword) {
		std::string inputPassword;
		unsigned char lastChar;
		while (true) {
			lastChar = _getch();
			if (lastChar == '\n' || lastChar == '\r') {
				unsigned short currentLength = inputPassword.size();
				if (settingPassword && currentLength < 8) {
					std::cout << "\r";
					utils::printPseudoPass(currentLength, ' ');
					std::cout << "\rMinimum password length is 8 characters" << std::endl;
					utils::printPseudoPass(currentLength);
				}
				else if (currentLength) {
					std::cout << std::endl;
					break;
				}
			}
			else if (lastChar == '\b' && inputPassword.size() != 0) {
				inputPassword.pop_back();
				std::cout << "\b \b";
			}
			else if (std::isprint(lastChar, std::locale("en")) && !isspace(lastChar)) {
				unsigned short currentLength = inputPassword.size();
				if((settingPassword && currentLength < 255) || (!settingPassword && currentLength < 65535)) {
					inputPassword += lastChar;
					std::cout << '*';
				}
				else {
					std::cout << "\r";
					utils::printPseudoPass(currentLength, ' ');
					std::cout << ((settingPassword) ? "\rMax password length is 255 characters" : "\rMax input length is 65535 characters") << std::endl;
					utils::printPseudoPass(currentLength);
				}
			}
			else if (lastChar == 27) {
				inputPassword.clear();
				break;
			}
		}
		return std::make_pair(inputPassword, lastChar);
	}

}