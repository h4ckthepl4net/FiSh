#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <filesystem>
#include <direct.h>
#include <vector>
#include <sstream>
#include <map>
#include <thread>
#include <mutex>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <windows.h>

#include "FiSh_utils.h"
#include "FiSh_constants.h"

namespace commands { 

	class ICommand {
	protected:
		int errCode = 0;
		bool paramsSet = false;
	public:
		virtual char setParams(std::vector<std::string>) = 0;
		virtual char execute() = 0;
	};

	class Root : public ICommand {
		friend class CommandFactory;
		class RootOperations : public ICommand {
			friend class CommandFactory;
		private:
			constants::RootOperationType operation = constants::RootOperationType::NO_OPERATION;
			RootOperations();
		public:
			virtual char setParams(std::vector<std::string>) override;
			virtual char execute() override;
		};
	private:
		static bool rootMode;
		ICommand* commandObj = nullptr;
		Root();
	public:
		static bool blockRoot();
		static bool isRootBlocked();
		static bool isRootMode();
		virtual char setParams(std::vector<std::string>) override;
		virtual char execute() override;
	};

	class Delete : public ICommand {
		friend class CommandFactory;
	private:
		std::string path;
		bool deleteEverything = false;
		Delete();
	public:
		virtual char setParams(std::vector<std::string>) override;
		virtual char execute() override;
	};
	class Add : public ICommand {
		friend class CommandFactory;
	private:
		std::string path;
		bool createFileIfMissing = false;
		bool appendData = false;
		int index = -1;
		Add();
	public:
		virtual char setParams(std::vector<std::string>) override;
		virtual char execute() override;
	};
	class Trunc : public ICommand {
		friend class CommandFactory;
	private:
		std::string path;
		bool addData = false;
		int index = -1;
		Trunc();
	public:
		virtual char setParams(std::vector<std::string>) override;
		virtual char execute() override;
	};
	class Output : public ICommand {
		friend class CommandFactory;
	private:
		std::string path;
		int index = -1;
		bool printStructure = false;
		Output();
	public:
		virtual char setParams(std::vector<std::string>) override;
		virtual char execute() override;
	};



	class CommandFactory {
	private:
		static std::mutex mtx;
		static std::map<std::string, ICommand*> instances;
		static Root::RootOperations* rootOperations;
		static ICommand* createInstance(std::string);
	public:
		static ICommand* getInstance(std::string);
		static ICommand* getRootOperationsObj();
		static void clearFactory();
	};

}

#endif
