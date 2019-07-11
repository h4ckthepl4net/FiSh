#include "pch.h"
#include "commands.h"

namespace commands {

	bool Root::rootMode = false;
	Root::Root() = default;
	char Root::setRootMode(std::string mode) {
		char errCode = 0;
		if (mode == "on") {
			if (!rootMode) {
				std::cout << "Please enter root password!" << std::endl;
				utils::checkIfPasswordIsSet();
				utils::requestPassword(false);
			}
			else {
				std::cout << "Root mode is already on!" << std::endl;
			}
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
		char errCode = 0;
		if (params.size() > 1) {
			std::transform(params[1].begin(), params[1].end(), params[1].begin(), ::tolower);
			while (params[1] == "root") {
				params.erase(params.begin());
				std::transform(params[1].begin(), params[1].end(), params[1].begin(), ::tolower);
			}
			this->commandObj = CommandFactory::getInstance(params[1]);
			if (this->commandObj == nullptr) {
				errCode = setRootMode(params[1]);
			}
			else {
				errCode = this->commandObj->setParams(params);
			}
		}
		else {
			// TODO: Add help message
		}
		return errCode;
	};
	char Root::execute() {
		char errCode = 0;
		if (commandObj) {
			this->commandObj->execute();
		}
		return errCode;
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
	ICommand* CommandFactory::addInstance(std::string clsName) {
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
				ICommand* result = addInstance(clsName);
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