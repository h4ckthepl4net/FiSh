#include "pch.h"
#include "commands.h"

namespace commands {

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
		if (clsName == "delete")
			cls = new Delete();
		else if (clsName == "add")
			cls = new Add;
		else if (clsName == "trunc")
			cls = new Trunc;
		else if (clsName == "output")
			cls = new Output;
		instances.emplace(clsName, cls);
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