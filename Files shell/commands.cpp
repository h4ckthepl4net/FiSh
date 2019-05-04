#include "pch.h"
#include "commands.h"

namespace commands {

	bool Root::rootMode = false;
	Root::Root() = default;
	char Root::setRootMode(std::string mode) {
		char errCode = 0;
		if (mode == "on") {
			
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
		char errCode;
		std::transform(params[1].begin(), params[1].end(), params[1].begin(), ::tolower);
		this->commandObj = CommandFactory::getInstance(params[1]);
		if (this->commandObj == nullptr) {
			errCode = setRootMode(params[1]);
		}
		else {
			errCode = this->commandObj->setParams(params);
		}
		return errCode;
	};
	char Root::execute() {
		char errCode = 0;
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
	std::map<std::string, Command*> CommandFactory::instances;
	Command* CommandFactory::addInstance(std::string clsName) {
		Command* cls = nullptr;
		if (clsName == "delete") {
			cls = new Delete();
			instances.emplace(clsName, cls);
		}
		else if (clsName == "add") {
			cls = new Add;
			instances.emplace(clsName, cls);
		}
		else if (clsName == "trunc") {
			cls = new Trunc;
			instances.emplace(clsName, cls);
		}
		else if (clsName == "output") {
			cls = new Output;
			instances.emplace(clsName, cls);
		}
		else if (clsName == "root") {
			cls = new Root;
			instances.emplace(clsName, cls);
		}
		return cls;
	}
	Command* CommandFactory::getInstance(std::string clsName) {
		std::transform(clsName.begin(), clsName.end(), clsName.begin(), ::tolower);
		if (instances.find(clsName) == instances.end()) {
			mtx.lock();
			if (instances.find(clsName) == instances.end()) {
				Command* result = addInstance(clsName);
				mtx.unlock();
				return result;
			}
			mtx.unlock();
		}
		return instances.find(clsName)->second;
	}

}