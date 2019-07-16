#include "pch.h"
#include "commands.h"

namespace commands {

	bool Root::rootMode = false;
	Root::Root() = default;
	char Root::setRootMode(std::string mode) {
		char errCode = 0;
		if (mode == "set") {
			constants::passwordIsSet passSet = utils::checkIfPasswordIsSet();
			if (passSet == constants::passwordIsSet::PASS_SET) {
				HKEY rootLockedKey;
				if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FilesShell\\RootModeBlocked", 0, KEY_QUERY_VALUE, &rootLockedKey) == ERROR_SUCCESS) {
					std::cout << "Root password is already set" << std::endl;
					std::string passFilePath = constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::defaultDirName + "\\.password";
					std::fstream passFile(passFilePath, std::fstream::in | std::fstream::binary);
					if (passFile.is_open()) {
						std::cout << "Enter current password to change it" << std::endl;
						std::pair<std::string, unsigned char> currentPassPair;
						do {
							std::cout << "Current password: ";
							currentPassPair = utils::requestPassword(false);
						} while (currentPassPair.second == 27 && !utils::askDecision());
						if (currentPassPair.second == 27) {
							std::cout << "Changing password canceled! Exiting..." << std::endl;
						}
						else {
							//TODO create hash of input password for security
							char passwordFromFile[256] = "";
							passFile.read(passwordFromFile, 256);
							if (currentPassPair.first == passwordFromFile) {
								while (true) {
									std::pair<std::string, unsigned char> newPassPair;
									do {
										std::cout << "New password: ";
										newPassPair = utils::requestPassword(true);
									} while (newPassPair.second == 27 && !utils::askDecision());
									if (newPassPair.second == 27) {
										std::cout << "Changing password canceled! Exiting..." << std::endl;
										break;
									}
									std::pair<std::string, unsigned char> confirmNewPassPair;
									do {
										std::cout << "Confirm new password: ";
										confirmNewPassPair = utils::requestPassword(true);
									} while (confirmNewPassPair.second == 27 && !utils::askDecision());
									if (confirmNewPassPair.second == 27) {
										std::cout << "Changing password canceled! Exiting..." << std::endl;
										break;
									}
									if (confirmNewPassPair.first == newPassPair.first) {
										std::fstream passwordTmpFile(passFilePath, std::fstream::out | std::fstream::trunc | std::fstream::binary);
										//TODO create hash of new password for security
										if (passwordTmpFile.is_open()) {
											passwordTmpFile.write(confirmNewPassPair.first.c_str(), confirmNewPassPair.first.size() + 1);
											break;
										}
										else {
											std::cout << "Couldn't set new password! Try again please..." << std::endl;
										}
									}
									else {
										std::cout << "New passwords don't match! Try again please..." << std::endl;
									}
								}
							}
							else {
								std::cout << "Current password is incorrect!" << std::endl;
							}
						}
					}
					else {
						std::cout << "Couldn't get current password! Exiting..." << std::endl;
					}
				}
				else {
					std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
				}
				RegCloseKey(rootLockedKey);
			}
			else if (passSet == constants::passwordIsSet::PASS_N_SET) {
				HKEY rootLockedKey;
				if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FilesShell\\RootModeBlocked", 0, KEY_QUERY_VALUE, &rootLockedKey) == ERROR_SUCCESS) {
					std::string passFilePath = constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::defaultDirName + "\\.password";
					if (!std::experimental::filesystem::exists(constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::defaultDirName)) {
						std::experimental::filesystem::create_directory(constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::defaultDirName);
						int fileAttr = GetFileAttributes((LPCWSTR)(constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::defaultDirName).c_str());
						if ((fileAttr & FILE_ATTRIBUTE_HIDDEN) == 0) {
							SetFileAttributes((LPCWSTR)passFilePath.c_str(), fileAttr | FILE_ATTRIBUTE_HIDDEN);
						}
					}
					while (true) {
						std::pair<std::string, unsigned char> newPassPair;
						do {
							std::cout << "New password: ";
							newPassPair = utils::requestPassword(true);
						} while (newPassPair.second == 27 && utils::askDecision());
						if (newPassPair.second == 27) {
							std::cout << "Setting password canceled! Exiting..." << std::endl;
							break;
						}
						std::pair<std::string, unsigned char> confirmNewPassPair;
						do {
							std::cout << "Confirm new password: ";
							confirmNewPassPair = utils::requestPassword(true);
						} while (confirmNewPassPair.second == 27 && utils::askDecision());
						if (confirmNewPassPair.second == 27) {
							std::cout << "Setting password canceled! Exiting..." << std::endl;
							break;
						}
						if (confirmNewPassPair.first == newPassPair.first) {
							HKEY key;
							if (RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FiSh\\isPassSet", NULL, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL) == ERROR_SUCCESS) {
								std::fstream passwordTmpFile(passFilePath, std::fstream::out | std::fstream::trunc | std::fstream::binary);
								//TODO create hash of new password for security
								if (passwordTmpFile.is_open()) {
									passwordTmpFile.write(confirmNewPassPair.first.c_str(), confirmNewPassPair.first.size() + 1);
									int fileAttr = GetFileAttributes((LPCWSTR)passFilePath.c_str());
									if ((fileAttr & FILE_ATTRIBUTE_HIDDEN) == 0) {
										SetFileAttributes((LPCWSTR)passFilePath.c_str(), fileAttr | FILE_ATTRIBUTE_HIDDEN);
									}
									std::cout << "Password is set! Exiting..." << std::endl;
								}
								else {
									std::cout << "Couldn't set new password! Try again please..." << std::endl;
								}
							}
							else {
								std::cout << "Couldn't set new password! Try again please..." << std::endl;

							}
							RegCloseKey(key);
						}
						else {
							std::cout << "New passwords don't match! Try again please..." << std::endl;
						}
					}
				}
				else {
					std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
				}
				RegCloseKey(rootLockedKey);
			}
			else if (passSet == constants::passwordIsSet::REG_KEY_E_PASS_FILE_N_E ||
				passSet == constants::passwordIsSet::REG_KEY_N_E_PASS_FILE_E) {
				HKEY key;
				RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FilesShell\\RootModeBlocked", NULL, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
				std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
				RegCloseKey(key);
			}
		}
		else if (mode == "del") {

		}
		else if (mode == "on") {

		}
		else if (mode == "off") {

		}
		else {

		}
		return errCode;
	};
	bool Root::isRootMode() {
		return rootMode;
	}
	char Root::setParams(std::vector<std::string> params) {
		if (params.size() > 1) {
			std::transform(params[1].begin(), params[1].end(), params[1].begin(), ::tolower);
			while (params[1] == "root") {
				params.erase(params.begin());
				std::transform(params[1].begin(), params[1].end(), params[1].begin(), ::tolower);
			}
			this->commandObj = CommandFactory::getInstance(params[1]);
			if (this->commandObj == nullptr) {
				this->errCode = setRootMode(params[1]);
			}
			else {
				this->errCode = this->commandObj->setParams(params);
			}
		}
		else {
			// TODO: Add help message
		}
		return this->errCode;
	};
	char Root::execute() {
		if (commandObj) {
			this->errCode = this->commandObj->execute();
		}
		return this->errCode;
	};

	Delete::Delete() = default;
	char Delete::setParams(std::vector<std::string> params) {
		std::transform(params[0].begin(), params[0].end(), params[0].begin(), tolower);
		if (params.size() == 2) {
			if (params[1] == "*") {

			}
			else if (std::experimental::filesystem::exists(params[1])) {

			}
		}
		else {

		}
		return 0;
	};
	char Delete::execute() {
		return 0;
	};

	Add::Add() = default;
	char Add::setParams(std::vector<std::string> params) {
		return 0;
	};
	char Add::execute() {
		return 0;
	};

	Trunc::Trunc() = default;
	char Trunc::setParams(std::vector<std::string>) {
		return 0;
	};
	char Trunc::execute() {
		return 0;
	};

	Output::Output() = default;
	char Output::setParams(std::vector<std::string>) {
		return 0;
	};
	char Output::execute() {
		return 0;
	};



	std::mutex CommandFactory::mtx;
	std::map<std::string, ICommand*> CommandFactory::instances;
	ICommand* CommandFactory::createInstance(std::string clsName) {
		ICommand* cls = nullptr;
		if (clsName == "delete") {
			cls = new Delete();
		}
		else if (clsName == "add") {
			cls = new Add;
		}
		else if (clsName == "trunc") {
			cls = new Trunc;
		}
		else if (clsName == "output") {
			cls = new Output;
		}
		else if (clsName == "root") {
			cls = new Root;
		}
		if (cls) {
			instances.emplace(clsName, cls);
		}
		return cls;
	}
	ICommand* CommandFactory::getInstance(std::string clsName) {
		std::transform(clsName.begin(), clsName.end(), clsName.begin(), ::tolower);
		if (instances.find(clsName) == instances.end()) {
			mtx.lock();
			if (instances.find(clsName) == instances.end()) {
				Command* result = createInstance(clsName);
				mtx.unlock();
				return result;
			}
			mtx.unlock();
		}
		return instances.find(clsName)->second;
	}
	void CommandFactory::clearFactory() {
		std::map<std::string, ICommand*>::iterator itStart;
		std::map<std::string, ICommand*>::iterator itEnd;
		for (itStart = instances.begin(), itEnd = instances.end(); itStart != itEnd; ++itStart) {
			delete itStart->second;
			itStart->second = nullptr;
		}
		instances.clear();
	}
}