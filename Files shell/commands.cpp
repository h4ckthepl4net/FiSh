#include "pch.h"
#include "commands.h"

namespace commands {

	bool Root::rootMode = false;
	Root::Root() = default;
	bool Root::blockRoot() {
		bool ret = false;
		HKEY key;
		if (RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FilesShell\\RootModeBlocked", NULL, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL) == ERROR_SUCCESS) {
			ret = true;
		}
		RegCloseKey(key);
		return ret;
	}
	bool Root::isRootBlocked() {
		HKEY rootLockedKey;
		return (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FilesShell\\RootModeBlocked", 0, KEY_QUERY_VALUE, &rootLockedKey) == ERROR_SUCCESS);
	}
	bool Root::isRootMode() {
		return rootMode;
	}
	char Root::setParams(std::vector<std::string> params) {
		// TODO: not using paramsSet field
		while(params.size() > 1) {
			std::transform(params[1].begin(), params[1].end(), params[1].begin(), ::tolower);
			if (params[1] == "root")
				params.erase(params.begin());
			else break;
		}
		if (params.size() > 1) {
			this->commandObj = CommandFactory::getInstance(params[1]);
			if (!this->commandObj) {
				this->commandObj = CommandFactory::getRootOperationsObj();
				this->errCode = this->commandObj->setParams(params);
			}
			else {
				if (!Root::isRootBlocked()) {
					constants::PasswordIsSet passSet = utils::checkIfPasswordIsSet();
					if (!Root::rootMode) {
						std::string passFilePath = constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::default_dir_name + "\\.password";
						if (passSet == constants::PasswordIsSet::PASS_SET) {
							std::fstream passFile(passFilePath, std::fstream::in | std::fstream::binary);
							if (passFile.is_open()) {
								std::cout << "Enter root password to execute the command!" << std::endl;
								std::pair<std::string, unsigned char> currentPassPair;
								do {
									std::cout << "Password: ";
									currentPassPair = utils::requestPassword(false);
								} while (currentPassPair.second == 27 && !utils::askDecision());
								if (currentPassPair.second == 27) {
									std::cout << "Command execution canceled! Exiting..." << std::endl;
								}
								else {
									// TODO: create hash of input password for security
									char passwordFromFile[256] = "";
									passFile.read(passwordFromFile, 256);
									if (currentPassPair.first == passwordFromFile) {
										this->errCode = this->commandObj->setParams(params);
									}
									else {
										std::cout << "Password is incorrect!" << std::endl;
									}
								}
							}
							else {
								std::cout << "Couldn't get root password for verifying! Exiting..." << std::endl;
							}
						}
						else if (passSet == constants::PasswordIsSet::PASS_N_SET) {
							std::cout << "Root password is not set! Please set root password and execute command again! Exiting..." << std::endl;
						}
						else if (passSet == constants::PasswordIsSet::REG_KEY_E_PASS_FILE_N_E ||
							passSet == constants::PasswordIsSet::REG_KEY_N_E_PASS_FILE_E) {
							if (Root::blockRoot()) {
								std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
							}
							else {
								std::cout << "Can't invoke that command now, please try again!" << std::endl;
							}
						}
					}
					else if (passSet == constants::PasswordIsSet::PASS_N_SET ||
							passSet == constants::PasswordIsSet::REG_KEY_E_PASS_FILE_N_E ||
							passSet == constants::PasswordIsSet::REG_KEY_N_E_PASS_FILE_E) {
						if (Root::blockRoot()) {
							std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
							Root::rootMode = false;
						}
						else {
							std::cout << "Can't invoke that command now, please try again!" << std::endl;
						}
					}
				}
				else {
					std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
				}
			}
		}
		else {
			// TODO: Add help message
		}
		return this->errCode;
	};
	char Root::execute() {
		// TODO: check paramsSet
		if (this->commandObj) {
			this->errCode = this->commandObj->execute();
		}
		return this->errCode;
	};
	void Root::reset() {
		this->errCode = 0;
		this->paramsSet = false; // TODO: not using paramsSet field
		this->commandObj->reset();
		this->commandObj = nullptr;
	}

	Root::RootOperations::RootOperations() = default;
	char Root::RootOperations::setParams(std::vector<std::string> params) {
		std::vector<std::string> operationArr = {"set", "remove", "on", "off"};
		auto it = std::find(operationArr.begin(), operationArr.end(), params[1]);
		if (it != operationArr.end()) {
			this->operation = static_cast<constants::RootOperationType>(it-operationArr.begin()+1);
			this->paramsSet = true;
		}
		else {
			// TODO: add error message
			this->operation = constants::RootOperationType::NO_OPERATION;
			this->paramsSet = false;
		}
		return this->errCode;
	};
	char Root::RootOperations::execute() {
		// TODO: close open files
		if (this->paramsSet && this->operation) {
			if (!Root::isRootBlocked()) {
				constants::PasswordIsSet passSet = utils::checkIfPasswordIsSet();
				std::string passFilePath = constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::default_dir_name + "\\.password";
				if (this->operation == constants::RootOperationType::SET_ROOT_PASS)
				{
					if (passSet == constants::PasswordIsSet::PASS_SET) {
						std::cout << "Root password is already set" << std::endl;
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
								// TODO: create hash of input password for security
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
											// TODO: create hash of new password for security
											if (passwordTmpFile.is_open()) {
												passwordTmpFile.write(confirmNewPassPair.first.c_str(), static_cast<unsigned long long int>(confirmNewPassPair.first.size()) + 1);
												std::cout << "Password is changed! Exiting..." << std::endl;
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
					else if (passSet == constants::PasswordIsSet::PASS_N_SET) {
						if (!std::experimental::filesystem::exists(constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::default_dir_name)) {
							std::experimental::filesystem::create_directory(constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::default_dir_name);
							int fileAttr = GetFileAttributesA((LPCSTR)(constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::default_dir_name).c_str());
							if ((fileAttr & FILE_ATTRIBUTE_HIDDEN) == 0) {
								SetFileAttributesA((LPCSTR)(constants::temp_path.u8string() + constants::temp_directory_name + "\\." + constants::default_dir_name).c_str(), fileAttr | FILE_ATTRIBUTE_HIDDEN);
							}
						}
						while (true) {
							std::pair<std::string, unsigned char> newPassPair;
							do {
								std::cout << "New password: ";
								newPassPair = utils::requestPassword(true);
							} while (newPassPair.second == 27 && !utils::askDecision());
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
									// TODO: create hash of new password for security
									if (passwordTmpFile.is_open()) {
										passwordTmpFile.write(confirmNewPassPair.first.c_str(), static_cast<long long int>(confirmNewPassPair.first.size()) + 1);
										int fileAttr = GetFileAttributesA((LPCSTR)passFilePath.c_str());
										if ((fileAttr & FILE_ATTRIBUTE_HIDDEN) == 0) {
											SetFileAttributesA((LPCSTR)passFilePath.c_str(), fileAttr | FILE_ATTRIBUTE_HIDDEN);
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
								break;
							}
							else {
								std::cout << "New passwords don't match! Try again please..." << std::endl;
							}
						}
					}
					else if (passSet == constants::PasswordIsSet::REG_KEY_E_PASS_FILE_N_E ||
						passSet == constants::PasswordIsSet::REG_KEY_N_E_PASS_FILE_E) {
						if (Root::blockRoot()) {
							std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
						}
						else {
							std::cout << "Can't invoke that command now, please try again!" << std::endl;
						}
					}
				}
				else if (this->operation == constants::RootOperationType::REMOVE_ROOT_PASS) {
					if (passSet == constants::PasswordIsSet::PASS_SET) {
						std::fstream passFile(passFilePath, std::fstream::in | std::fstream::binary);
						if (passFile.is_open()) {
							std::cout << "Enter current password to remove existing password!" << std::endl;
							std::pair<std::string, unsigned char> currentPassPair;
							do {
								std::cout << "Current password: ";
								currentPassPair = utils::requestPassword(false);
							} while (currentPassPair.second == 27 && !utils::askDecision());
							if (currentPassPair.second == 27) {
								std::cout << "Removing password canceled! Exiting..." << std::endl;
							}
							else {
								char passwordFromFile[256] = "";
								passFile.read(passwordFromFile, 256);
								if (currentPassPair.first == passwordFromFile) {
									passFile.close();
									std::remove(passFilePath.c_str());
									RegDeleteKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\FiSh\\isPassSet", KEY_WOW64_64KEY, 0);
									std::cout << "Password is removed! Exiting..." << std::endl;
								}
								else {
									std::cout << "Current password is incorrect! Please try the command again..." << std::endl;
								}
							}
						}
						else {
							std::cout << "Couldn't get current password! Exiting..." << std::endl;
						}
					}
					else if (passSet == constants::PasswordIsSet::PASS_N_SET) {
						std::cout << "Root password is not set! Exiting..." << std::endl;
					}
					else if (passSet == constants::PasswordIsSet::REG_KEY_E_PASS_FILE_N_E ||
						passSet == constants::PasswordIsSet::REG_KEY_N_E_PASS_FILE_E) {
						if (Root::blockRoot()) {
							std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
						}
						else {
							std::cout << "Can't invoke that command now, please try again!" << std::endl;
						}
					}
				}
				else if (this->operation == constants::RootOperationType::ON_ROOT_MODE) {
					if (Root::rootMode) {
						if (passSet == constants::PasswordIsSet::PASS_N_SET ||
							passSet == constants::PasswordIsSet::REG_KEY_E_PASS_FILE_N_E ||
							passSet == constants::PasswordIsSet::REG_KEY_N_E_PASS_FILE_E) {
							if (Root::blockRoot()) {
								std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
							}
							else {
								std::cout << "Can't invoke that command now, please try again!" << std::endl;
							}
						}
						else {
							std::cout << "Root mode is already turned on! Exiting..." << std::endl;
						}
					}
					else {
						if (passSet == constants::PasswordIsSet::PASS_SET) {
							std::fstream passFile(passFilePath, std::fstream::in | std::fstream::binary);
							if (passFile.is_open()) {
								std::cout << "Enter current password to turn on root mode!" << std::endl;
								std::pair<std::string, unsigned char> currentPassPair;
								do {
									std::cout << "Current password: ";
									currentPassPair = utils::requestPassword(false);
								} while (currentPassPair.second == 27 && !utils::askDecision());
								if (currentPassPair.second == 27) {
									std::cout << "Turning root mode on canceled! Exiting..." << std::endl;
								}
								else {
									// TODO: create hash of input password for security
									char passwordFromFile[256] = "";
									passFile.read(passwordFromFile, 256);
									if (currentPassPair.first == passwordFromFile) {
										Root::rootMode = true;
										std::cout << "Root mode is turned on now! Exiting..." << std::endl;
									}
									else {
										std::cout << "Password is incorrect, can't turn on root mode! Exiting..." << std::endl;
									}
								}
							}
							else {
								std::cout << "Couldn't get current password! Exiting..." << std::endl;
							}
						}
						else if (passSet == constants::PasswordIsSet::PASS_N_SET) {
							std::cout << "Root password is not set! Please set root password to turn on root mode! Exiting..." << std::endl;
						}
						else if (passSet == constants::PasswordIsSet::REG_KEY_E_PASS_FILE_N_E ||
							passSet == constants::PasswordIsSet::REG_KEY_N_E_PASS_FILE_E) {
							if (Root::blockRoot()) {
								std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
							}
							else {
								std::cout << "Can't invoke that command now, please try again!" << std::endl;
							}
						}
					}
				}
				else if (this->operation == constants::RootOperationType::OFF_ROOT_MODE) {
					if(Root::rootMode) {
						if (passSet == constants::PasswordIsSet::PASS_SET) {
							Root::rootMode = false;
							std::cout << "Root mode is turned off now! Exiting..." << std::endl;
						}
						else if (passSet == constants::PasswordIsSet::PASS_N_SET ||
							passSet == constants::PasswordIsSet::REG_KEY_E_PASS_FILE_N_E ||
							passSet == constants::PasswordIsSet::REG_KEY_N_E_PASS_FILE_E) {
							if (Root::blockRoot()) {
								std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
							}
							else {
								std::cout << "Can't invoke that command now, please try again!" << std::endl;
							}
						}
					}
					else {
						if (passSet == constants::PasswordIsSet::PASS_SET ||
							passSet == constants::PasswordIsSet::PASS_N_SET) {
							std::cout << "Root mode is already turned off! Exiting..." << std::endl;
						}
						else {
							if (Root::blockRoot()) {
								std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
							}
							else {
								std::cout << "Can't invoke that command now, please try again!" << std::endl;
							}
						}
					}
				}
				else {
					// TODO: add error message
				}
			}
			else {
				std::cout << "Something went wrong, cause root mode is blocked for you!" << std::endl;
			}
		}
		else {
			// TODO: add error message (wrong params)
		}
		return this->errCode;
	};
	void Root::RootOperations::reset() {
		this->errCode = 0;
		this->paramsSet = false;
		this->operation = constants::RootOperationType::NO_OPERATION;
	}

	Delete::Delete() = default;
	char Delete::setParams(std::vector<std::string> params) {		
		std::transform(params[0].begin(), params[0].end(), params[0].begin(), tolower);
		if (params[0] == "root") {
			this->isExecutedAsRoot = true;
			params.erase(params.begin());
		}
		if (params.size() == 2) {
			if (params[1] == "*" && !this->isExecutedAsRoot && !Root::isRootMode()) {
				this->deleteEverything = true;
				this->paramsSet = true;
			}
			else if (params[1] == "*" && (this->isExecutedAsRoot || Root::isRootMode())) {
				// TODO: add error code (cannot exec delete all in root mode [Dangerous!])
			}
			else {
				std::experimental::filesystem::path inputPath = params[1];
				inputPath.make_preferred();
				if (inputPath.is_relative()) {
					inputPath = "./files directory" / inputPath;
				}
				inputPath = std::experimental::filesystem::absolute(inputPath);
				if (utils::isInWorkingDirectory(inputPath) || this->isExecutedAsRoot || commands::Root::isRootMode()) {
					this->path = inputPath.u8string();
					this->paramsSet = true;
				}
				else {
					// TODO: add error code (cannot exec delete file outside working dir without root mode [Dangerous!])
				}
			}
		}
		else {
			// TODO: add error code (no enough params)
		}
		return 0;
	};
	char Delete::execute() {
		if (this->paramsSet) {
			if (this->deleteEverything) {
				if (!this->isExecutedAsRoot) {
					if (utils::askDecision("Are you sure you want to delete everything in working directory? (Y/N)")) {
						uintmax_t itemsDeleted = 0;
						for (auto &file : std::experimental::filesystem::directory_iterator("./files directory/")) {
							bool isDirectory = std::experimental::filesystem::is_directory(file.path());
							std::experimental::filesystem::remove_all(file.path());
							itemsDeleted++;
							if (itemsDeleted <= 25) {
								std::cout << ((isDirectory) ? "_!*Dir*!_   " : "") << file.path() << std::endl;
							}
						}
						if (itemsDeleted > 25) {
							std::cout << "...and " << itemsDeleted - 25 << " more!" << std::endl;
						}
						std::cout << "Deleted " << itemsDeleted << " items! Exiting..." << std::endl;
					}
					else {
						std::cout << "Command execution canceled! Exiting..." << std::endl;
					}
				}
				else {
					// TODO: add error code (cannot exec delete all in root mode [Dangerous!])
				}
			}
			else if (this->path != "") {
				if (this->path.find('/') == std::string::npos && this->path.find('*') == std::string::npos &&
					this->path.find('?') == std::string::npos && this->path.find('"') == std::string::npos &&
					this->path.find('<') == std::string::npos && this->path.find('>') == std::string::npos &&
					this->path.find('|') == std::string::npos) {
					if (std::experimental::filesystem::exists(this->path)) {
						if (!std::experimental::filesystem::is_directory(this->path)) {							
							if (utils::askDecision("Are you sure you want delete selected file? (Y/N)")) {
								std::experimental::filesystem::remove(this->path);
							}
							else {
								std::cout << std::endl << "Command execution canceled! Exiting..." << std::endl;
							}
						}
						else {
							std::cout << std::endl << "Selected object is directory" << std::endl;
							if (utils::askDecision("Do you want to delete directory and everything inside? (Y/N)")) {
								std::experimental::filesystem::remove_all(this->path);
							}
							else {
								std::cout << std::endl << "Command execution canceled! Exiting..." << std::endl;
							}
						}
					}
					else {
						std::cout << "No such file found! Exiting..." << std::endl;
					}
				}
				else {
					// TODO: add error message file name is not correct
				}
			}
		}
		else {
			// TODO: add error code (params not set)
		}
		return 0;
	};
	void Delete::reset() {
		this->errCode = 0;
		this->paramsSet = false;
		this->isExecutedAsRoot = false;
		this->path = "";
		this->deleteEverything = false;
	}

	Add::Add() = default;
	char Add::setParams(std::vector<std::string> params) {
		return 0;
	};
	char Add::execute() {
		return 0;
	};
	void Add::reset() {
		this->errCode = 0;
		this->paramsSet = false;
		this->isExecutedAsRoot = false;
		this->path = "";
		this->createFileIfMissing = false;
		this->appendData = false;
		this->index = -1;
	}

	Trunc::Trunc() = default;
	char Trunc::setParams(std::vector<std::string>) {
		return 0;
	};
	char Trunc::execute() {
		return 0;
	};
	void Trunc::reset() {
		this->errCode = 0;
		this->paramsSet = false;
		this->isExecutedAsRoot = false;
		this->path = "";
		this->addData = false;
		this->index = -1;
	}

	Output::Output() = default;
	char Output::setParams(std::vector<std::string>) {
		return 0;
	};
	char Output::execute() {
		return 0;
	};
	void Output::reset() {
		this->errCode = 0;
		this->paramsSet = false;
		this->isExecutedAsRoot = false;
		this->path = "";
		this->index = -1;
		this->printStructure = false;
	}



	std::mutex CommandFactory::mtx;
	std::map<std::string, ICommand*> CommandFactory::instances;
	Root::RootOperations* CommandFactory::rootOperations = nullptr;
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
				ICommand* result = createInstance(clsName);
				mtx.unlock();
				return result;
			}
			mtx.unlock();
		}
		return instances.find(clsName)->second;
	}
	ICommand* CommandFactory::getRootOperationsObj() {
		if (!CommandFactory::rootOperations) {
			mtx.lock();
			if (!CommandFactory::rootOperations) {
				CommandFactory::rootOperations = new Root::RootOperations;
			}
			mtx.unlock();
		}
		return CommandFactory::rootOperations;
	}
	void CommandFactory::clearFactory() {
		std::map<std::string, ICommand*>::iterator itStart;
		std::map<std::string, ICommand*>::iterator itEnd;
		for (itStart = instances.begin(), itEnd = instances.end(); itStart != itEnd; ++itStart) {
			delete itStart->second;
			itStart->second = nullptr;
		}
		instances.clear();
		if (CommandFactory::rootOperations) {
			delete CommandFactory::rootOperations;
			CommandFactory::rootOperations = nullptr;
		}
	}
}