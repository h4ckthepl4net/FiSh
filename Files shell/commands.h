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

namespace commands { 

	class ICommand {
	private:
		bool paramsSet = false;
	public:
		virtual char setParams(std::vector<std::string>) = 0;
		virtual char execute() = 0;
	};

	class Root : ICommand {
		friend class CommandFactory;
	private:
		static bool rootMode;
		ICommand* commandObj = nullptr;
		Root();
	public:
		static char setRootMode(std::string mode);
		static bool isRootMode();
		virtual char setParams(std::vector<std::string>) override;
		virtual char execute() override;
	};

	class Delete : ICommand {
		friend class CommandFactory;
	private:
		std::string path;
		bool deleteEverything = false;
		Delete();
	public:
		virtual char setParams(std::vector<std::string>) override;
		virtual char execute() override;
	};
	class Add : ICommand {
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
	class Trunc : ICommand {
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
	class Output : ICommand {
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
		static ICommand* addInstance(std::string);
	public:
		static ICommand* getInstance(std::string);
	};

}

#endif
