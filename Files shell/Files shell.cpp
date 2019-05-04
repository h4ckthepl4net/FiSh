// College problems.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
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

#include "commands.h"
#include "data_types.h"
#include "FiSh_utils.h"
#include "FiSh_constants.h"

//#define DEBUG

namespace filesystem = std::experimental::filesystem;

int main()
{
	utils::requestPassword(true);
	/*utils::getProgramTempDirectoryPath();
	std::vector<std::string> inputCommand = utils::readCommand();
	commands::Command* commandObject = commands::CommandFactory::getInstance(inputCommand[0]);
	commandObject->setParams(inputCommand);*/
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
//

//bool exitFlag = false;
//do {
//	std::cout << std::endl << "Press:" << std::endl
//		<< "0. Clear specific file if exists," << std::endl
//		<< "1. Clear specific file if exists and write new data," << std::endl
//		<< "2. Clear data at specific index from specific file if file and data exists," << std::endl
//		<< "3. Add data to existing file," << std::endl
//		<< "4. Add data to specific index in specific file," << std::endl
//		<< "5. Create file and add data," << std::endl
//		<< "6. Output all data from specific file," << std::endl
//		<< "7. Output data at specific index from specific file," << std::endl
//		<< "8. Change data at specific index in specific file," << std::endl
//		<< "9. Delete specific file," << std::endl
//		<< "?. Show existing files," << std::endl
//		<< "DELETE. Delete everything in directory," << std::endl
//		<< "ESC. Exit." << std::endl;
//	char c = _getch();
//	if (c == 27) {
//		exitFlag = askDecision("Are you sure you want to exit? (Y/N)");
//	}
//	else if (c == -32) {
//		std::string decision;
//		do {
//			std::cout << std::endl << "Are you sure you want to delete everything in directory? (Y/N)" << std::endl;
//			std::cin >> decision;
//		} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//		if (decision == "Y" || decision == "y") {
//			uintmax_t filesDeleted = 0;
//			for (auto &file : std::experimental::filesystem::directory_iterator("./files directory/")) {
//				if (std::experimental::filesystem::is_directory(file.path())) {
//					filesDeleted++;
//				}
//				std::cout << file.path() << std::endl;
//				filesDeleted += std::experimental::filesystem::remove_all(file.path());
//			}
//			std::cout << std::endl << "Deleted " << filesDeleted << " files." << std::endl;
//		}
//		else {
//			std::cout << std::endl << "Operation canceled." << std::endl;
//		}
//	}
//	else if (c == '?') {
//		if (std::experimental::filesystem::is_empty("./files directory/")) {
//			std::cout << std::endl << "Directory is empty" << std::endl;
//		}
//		else {
//			std::string tmp = std::experimental::filesystem::current_path().u8string();
//			tmp = "tree \"" + tmp + "\\files directory\" /F > tree_struct.txt";
//			system(tmp.c_str());
//			std::fstream treeStructure("tree_struct.txt", std::fstream::in);
//			std::cout << "Files\t" << (char)191 << std::endl;
//			if (treeStructure.is_open() && treeStructure.good()) {
//				int i = 0;
//				while (std::getline(treeStructure, tmp)) {
//					if (i > 2) {
//						std::cout << "\t" + tmp << std::endl;
//					}
//					else
//						++i;
//				}
//			}
//			treeStructure.close();
//		}
//	}
//	else if (c == '0') {
//		std::string tmp;
//		do {
//			std::cout << "Enter file name (Can not contain /\\:*?\"<>|): ";
//			std::getline(std::cin, tmp);
//		} while (tmp.find('/') != std::string::npos || tmp.find('\\') != std::string::npos ||
//			tmp.find(':') != std::string::npos || tmp.find('*') != std::string::npos ||
//			tmp.find('?') != std::string::npos || tmp.find('"') != std::string::npos ||
//			tmp.find('<') != std::string::npos || tmp.find('>') != std::string::npos ||
//			tmp.find('|') != std::string::npos);
//		if (std::experimental::filesystem::exists("./files directory/" + tmp)) {
//			if (!std::experimental::filesystem::is_directory("./files directory/" + tmp)) {
//				std::string decision;
//				do {
//					std::cout << std::endl << "Are you sure you want to clear file? (Y/N)" << std::endl;
//					std::cin >> decision;
//				} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//
//				if (decision == "Y" || decision == "y") {
//					std::fstream f("./files directory/" + tmp, std::fstream::out | std::fstream::trunc);
//					f.close();
//				}
//				else {
//					std::cout << std::endl << "Operation canceled." << std::endl;
//				}
//			}
//			else {
//				std::cout << std::endl << "Selected object is directory" << std::endl;
//			}
//		}
//		else {
//			std::cout << "No such file found!" << std::endl;
//		}
//	}
//	else if (c == '1') {
//		std::string tmp;
//		do {
//			std::cout << "Enter file name (Can not contain /\\:*?\"<>|): ";
//			std::getline(std::cin, tmp);
//		} while (tmp.find('/') != std::string::npos || tmp.find('\\') != std::string::npos ||
//			tmp.find(':') != std::string::npos || tmp.find('*') != std::string::npos ||
//			tmp.find('?') != std::string::npos || tmp.find('"') != std::string::npos ||
//			tmp.find('<') != std::string::npos || tmp.find('>') != std::string::npos ||
//			tmp.find('|') != std::string::npos);
//		bool foundFile = false;
//		std::fstream f;
//		if (std::experimental::filesystem::exists("./files directory/" + tmp)) {
//			if (!std::experimental::filesystem::is_directory("./files directory/" + tmp)) {
//				std::string decision;
//				do {
//					std::cout << std::endl << "Are you sure you want to clear file and write new data? (Y/N)" << std::endl;
//					std::cin >> decision;
//				} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//
//				if (decision == "Y" || decision == "y") {
//					foundFile = true;
//				}
//				else {
//					std::cout << std::endl << "Operation canceled." << std::endl;
//				}
//			}
//			else {
//				std::cout << std::endl << "Selected object is directory" << std::endl;
//			}
//		}
//		else {
//			std::cout << "No such file found!" << std::endl;
//		}
//		if (foundFile) {
//			char decisionChr;
//			do {
//				std::cout << std::endl << "Select content type:" << std::endl
//					<< "0. Enter data for student," << std::endl
//					<< "1. Enter data for lecturer," << std::endl
//					<< "2. Enter data for group," << std::endl
//					<< "ESC. Exit." << std::endl;
//				decisionChr = _getch();
//				if (decisionChr == 27) {
//					std::string decision;
//					do
//					{
//						std::cout << std::endl << "Are you sure you want to exit? (Y/N)" << std::endl;
//						std::cin >> decision;
//					} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//					if (decision == "Y" || decision == "y") {
//						break;
//					}
//					else {
//						decisionChr = -32;
//						continue;
//					}
//				}
//			} while (decisionChr != '0' && decisionChr != '1' && decisionChr != '2');
//			char isBin;
//			if (decisionChr != 27) {
//				do {
//					std::cout << std::endl << "Select data type:" << std::endl
//						<< "0. Save as binary," << std::endl
//						<< "1. Save as ASCII," << std::endl
//						<< "ESC. Exit." << std::endl;
//					isBin = _getch();
//					if (isBin == 27) {
//						std::string decision;
//						do
//						{
//							std::cout << std::endl << "Are you sure you want to exit? (Y/N)" << std::endl;
//							std::cin >> decision;
//						} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//						if (decision == "Y" || decision == "y") {
//							break;
//						}
//						else {
//							isBin = -32;
//							continue;
//						}
//					}
//				} while (isBin != '0' && isBin != '1');
//				if (isBin != 27) {
//					std::cout << "Enter data count: ";
//					int dataCount;
//					std::cin >> dataCount;
//					if (isBin == '0') {
//						f.open("./files directory/" + tmp, std::fstream::out | std::fstream::trunc | std::fstream::binary);
//						if (decisionChr == '0') {
//							int classType = CollegeData::fileType::StudentFileBin;
//							f.write((char *)&classType, sizeof(int));
//							for (int i = 0; i < dataCount; i++) {
//								StudentData obj;
//								std::cout << "\n\nEnter data for student N" << i + 1 << std::endl;
//								std::cout << "Name: "; std::cin >> obj.name;
//								std::cout << "Surname: "; std::cin >> obj.surname;
//								std::cout << "Patronymic: "; std::cin >> obj.patronymic;
//								std::cout << "Group: "; std::cin >> obj.groupCode;
//								std::cout << "Absent count: "; std::cin >> obj.absentCnt;
//								std::cout << "Average mark: "; std::cin >> obj.avgMark;
//								f.write((char *)&obj, sizeof(StudentData));
//							}
//						}
//						else if (decisionChr == '1') {
//							int classType = CollegeData::fileType::LecturerFileBin;
//							f.write((char *)&classType, sizeof(classType));
//							for (int i = 0; i < dataCount; i++) {
//								LecturerData obj;
//								std::cout << "\n\nEnter data for lecturer N" << i + 1 << std::endl;
//								std::cout << "Name: "; std::cin >> obj.name;
//								std::cout << "Surname: "; std::cin >> obj.surname;
//								std::cout << "Salary: "; std::cin >> obj.salary;
//								std::cout << "Group code where lecturer is class teacher: "; std::cin >> obj.classTeachedOf;
//								std::cout << "Groups where lecturer teaches (separated by ,): "; std::cin >> obj.lecturerIn;
//								std::cout << "Subjects that lecturer teaches (separated by ,): "; std::cin >> obj.lecturerSubjects;
//								f.write((char *)&obj, sizeof(LecturerData));
//							}
//						}
//						else if (decisionChr == '2') {
//							int classType = CollegeData::fileType::GroupFileBin;
//							f.write((char *)&classType, sizeof(classType));
//							for (int i = 0; i < dataCount; i++) {
//								GroupData obj;
//								std::cout << "\n\nEnter data for group N" << i + 1 << std::endl;
//								std::cout << "Group name: "; std::cin >> obj.groupName;
//								std::cout << "Class teacher: "; std::cin >> obj.classTeacher;
//								std::cout << "Group faculty: "; std::cin >> obj.groupFaculty;
//								std::cout << "Course of students: "; std::cin >> obj.studentsCourse;
//								std::cout << "Students count: "; std::cin >> obj.studentsCount;
//								f.write((char *)&obj, sizeof(GroupData));
//							}
//						}
//					}
//					else {
//						f.open("./files directory/" + tmp, std::fstream::out | std::fstream::trunc);
//						if (decisionChr == '0') {
//							int classType = CollegeData::fileType::StudentFile;
//							f.write((char *)&classType, sizeof(classType));
//							f << std::endl;
//							for (int i = 0; i < dataCount; i++) {
//								std::string tempStr;
//								f << "{\n";
//								std::cout << "\n\nEnter data for student N" << i + 1 << std::endl;
//								std::cout << "Name: ";
//								std::cin >> tempStr;
//								f << "$name:" << tempStr << ";\n";
//								std::cout << "Surname: ";
//								std::cin >> tempStr;
//								f << "$surname:" << tempStr << ";\n";
//								std::cout << "Patronymic: ";
//								std::cin >> tempStr;
//								f << "$patronymic:" << tempStr << ";\n";
//								std::cout << "Group: ";
//								std::cin >> tempStr;
//								f << "$group:" << tempStr << ";\n";
//								std::cout << "Absent count: ";
//								std::cin >> tempStr;
//								f << "$absentCount:" << tempStr << ";\n";
//								std::cout << "Average mark: ";
//								std::cin >> tempStr;
//								f << "$avgMark:" << tempStr << ";\n";
//								f << "}\n";
//							}
//						}
//						else if (decisionChr == '1') {
//							int classType = CollegeData::fileType::LecturerFile;
//							f.write((char *)&classType, sizeof(classType));
//							f << std::endl;
//							for (int i = 0; i < dataCount; i++) {
//								std::string tempStr;
//								f << "{\n";
//								std::cout << "\n\nEnter data for lecturer N" << i + 1 << std::endl;
//								std::cout << "Name: ";
//								std::cin >> tempStr;
//								f << "$name:" << tempStr << ";\n";
//								std::cout << "Surname: ";
//								std::cin >> tempStr;
//								f << "$surname:" << tempStr << ";\n";
//								std::cout << "Salary: ";
//								std::cin >> tempStr;
//								f << "$salary:" << tempStr << ";\n";
//								std::cout << "Group code where lecturer is class teacher: ";
//								std::cin >> tempStr;
//								f << "$classTeacherOf:" << tempStr << ";\n";
//								std::cout << "Groups where lecturer teaches (separated by ,): ";
//								std::cin >> tempStr;
//								f << "$lecturerIn:" << tempStr << ";\n";
//								std::cout << "Subjects that lecturer teaches (separated by ,): ";
//								std::cin >> tempStr;
//								f << "$lecturerSubjects:" << tempStr << ";\n";
//								f << "}\n";
//							}
//						}
//						else if (decisionChr == '2') {
//							int classType = CollegeData::fileType::GroupFile;
//							f.write((char *)&classType, sizeof(classType));
//							f << std::endl;
//							for (int i = 0; i < dataCount; i++) {
//								std::string tempStr;
//								f << "{\n";
//								std::cout << "\n\nEnter data for group N" << i + 1 << std::endl;
//								std::cout << "Group name: ";
//								std::cin >> tempStr;
//								f << "$groupName:" << tempStr << ";\n";
//								std::cout << "Class teacher: ";
//								std::cin >> tempStr;
//								f << "$classTeacher:" << tempStr << ";\n";
//								std::cout << "Group faculty: ";
//								std::cin >> tempStr;
//								f << "$groupFaculty:" << tempStr << ";\n";
//								std::cout << "Course of students: ";
//								std::cin >> tempStr;
//								f << "$studentsCourse:" << tempStr << ";\n";
//								std::cout << "Students count: ";
//								std::cin >> tempStr;
//								f << "$studentsCount:" << tempStr << ";\n";
//								f << "}\n";
//							}
//						}
//					}
//					f.close();
//				}
//			}
//		}
//	}
//	else if (c == '2') {
//		std::string tmp;
//		do {
//			std::cout << "Enter file name (Can not contain /\\:*?\"<>|): ";
//			std::getline(std::cin, tmp);
//		} while (tmp.find('/') != std::string::npos || tmp.find('\\') != std::string::npos ||
//			tmp.find(':') != std::string::npos || tmp.find('*') != std::string::npos ||
//			tmp.find('?') != std::string::npos || tmp.find('"') != std::string::npos ||
//			tmp.find('<') != std::string::npos || tmp.find('>') != std::string::npos ||
//			tmp.find('|') != std::string::npos);
//		bool foundFile = false;
//		std::fstream f;
//		if (std::experimental::filesystem::exists("./files directory/" + tmp)) {
//			if (!std::experimental::filesystem::is_directory("./files directory/" + tmp)) {
//				std::string decision;
//				do {
//					std::cout << std::endl << "Are you sure you want to clear data at selected index in selected file? (Y/N)" << std::endl;
//					std::cin >> decision;
//				} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//
//				if (decision == "Y" || decision == "y") {
//					f.open("./files directory/" + tmp, std::fstream::out | std::fstream::in);
//					foundFile = true;
//				}
//				else {
//					std::cout << std::endl << "Operation canceled." << std::endl;
//				}
//			}
//			else {
//				std::cout << std::endl << "Selected object is directory" << std::endl;
//			}
//		}
//		else {
//			std::cout << "No such file found!" << std::endl;
//		}
//		if (foundFile) {
//			std::cout << "Enter index: " << std::endl;
//			int index;
//			std::cin >> index;
//			CollegeData::fileType type;
//			f.read((char *)&type, sizeof(int));
//			if (f.is_open()) {
//				f.close();
//				f.clear();
//			}
//			if (type == CollegeData::fileType::StudentFile ||
//				type == CollegeData::fileType::LecturerFile ||
//				type == CollegeData::fileType::GroupFile) {
//				f.open("./files directory/" + tmp, std::fstream::out | std::fstream::in);
//				f.seekg(sizeof(int), std::ios::beg);
//				std::fstream tempFile("./files directory/A6864EB339B0E1F6E00D75293A8840ABF069A2C0FE82E6E53AF6AC099793C1D5.txt", std::fstream::out | std::fstream::trunc);
//				tempFile.write((char*)&type, sizeof(int));
//				tempFile << std::endl;
//				std::string line;
//				int currentInd = -1;
//				while (!f.eof()) {
//					std::getline(f, line);
//					if (line.find("{") != std::string::npos) {
//						++currentInd;
//					}
//					if (currentInd != index) {
//						tempFile << line << std::endl;
//					}
//				}
//				f.close();
//				f.clear();
//				tempFile.close();
//				tempFile.clear();
//				f.open("./files directory/" + tmp, std::fstream::out | std::fstream::trunc);
//				tempFile.open("./files directory/A6864EB339B0E1F6E00D75293A8840ABF069A2C0FE82E6E53AF6AC099793C1D5.txt", std::fstream::in);
//				while (!tempFile.eof()) {
//					std::getline(tempFile, line);
//					f << line << std::endl;
//				}
//				f.close();
//				tempFile.close();
//				std::remove("./files directory/A6864EB339B0E1F6E00D75293A8840ABF069A2C0FE82E6E53AF6AC099793C1D5.txt");
//			}
//			else if (type == CollegeData::fileType::StudentFileBin ||
//				type == CollegeData::fileType::LecturerFileBin ||
//				type == CollegeData::fileType::GroupFileBin) {
//				f.open("./files directory/" + tmp, std::fstream::out | std::fstream::in | std::fstream::binary);
//				f.seekg(sizeof(int), std::ios::beg);
//				std::vector<CollegeData*> fileData;
//				while (!f.eof() && f.good()) {
//					CollegeData *newObj;
//					if (type == CollegeData::fileType::StudentFileBin) {
//						newObj = new StudentData;
//						f.read((char*)newObj, sizeof(StudentData));
//					}
//					else if (type == CollegeData::fileType::LecturerFileBin) {
//						newObj = new LecturerData;
//						f.read((char*)newObj, sizeof(LecturerData));
//					}
//					else {
//						newObj = new GroupData;
//						f.read((char*)newObj, sizeof(GroupData));
//					}
//					if (!f.eof()) {
//						fileData.push_back(newObj);
//					}
//				}
//				f.close();
//				f.clear();
//				f.open("./files directory/" + tmp, std::fstream::out | std::fstream::trunc | std::fstream::binary);
//				f.write((char *)&type, sizeof(int));
//				for (unsigned int ind = 0; ind < fileData.size(); ind++) {
//					if (ind != index) {
//						if (type == CollegeData::fileType::StudentFileBin) {
//							f.write((char *)((StudentData*)fileData[ind]), sizeof(StudentData));
//						}
//						else if (type == CollegeData::fileType::LecturerFileBin) {
//							f.write((char *)((LecturerData*)fileData[ind]), sizeof(LecturerData));
//						}
//						else {
//							f.write((char *)((GroupData*)fileData[ind]), sizeof(GroupData));
//						}
//					}
//					delete fileData[ind];
//				}
//				f.close();
//			}
//		}
//	}
//	else if (c == '3') {
//		std::string tmp;
//		do {
//			std::cout << "Enter file name (Can not contain /\\:*?\"<>|): ";
//			std::getline(std::cin, tmp);
//		} while (tmp.find('/') != std::string::npos || tmp.find('\\') != std::string::npos ||
//			tmp.find(':') != std::string::npos || tmp.find('*') != std::string::npos ||
//			tmp.find('?') != std::string::npos || tmp.find('"') != std::string::npos ||
//			tmp.find('<') != std::string::npos || tmp.find('>') != std::string::npos ||
//			tmp.find('|') != std::string::npos);
//		bool foundFile = false;
//		std::fstream f;
//		if (std::experimental::filesystem::exists("./files directory/" + tmp)) {
//			if (!std::experimental::filesystem::is_directory("./files directory/" + tmp)) {
//				std::string decision;
//				do {
//					std::cout << std::endl << "Are you sure you want to add data to selected file? (Y/N)" << std::endl;
//					std::cin >> decision;
//				} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//
//				if (decision == "Y" || decision == "y") {
//					f.open("./files directory/" + tmp, std::fstream::out | std::fstream::in | std::fstream::app);
//					foundFile = true;
//				}
//				else {
//					std::cout << std::endl << "Operation canceled." << std::endl;
//				}
//			}
//			else {
//				std::cout << std::endl << "Selected object is directory" << std::endl;
//			}
//		}
//		else {
//			std::cout << "No such file found!" << std::endl;
//		}
//		if (foundFile) {
//			CollegeData::fileType type;
//			f.read((char *)&type, sizeof(int));
//			if (f.is_open()) {
//				f.close();
//				f.clear();
//			}
//			std::cout << "Enter data count: ";
//			int dataCount;
//			std::cin >> dataCount;
//			if (type == CollegeData::fileType::StudentFileBin ||
//				type == CollegeData::fileType::LecturerFileBin ||
//				type == CollegeData::fileType::GroupFileBin) {
//				f.open("./files directory/" + tmp, std::fstream::out | std::fstream::in | std::fstream::app | std::fstream::binary);
//				if (type == CollegeData::fileType::StudentFileBin) {
//					for (int i = 0; i < dataCount; i++) {
//						StudentData obj;
//						std::cout << "\n\nEnter data for student N" << i + 1 << std::endl;
//						std::cout << "Name: "; std::cin >> obj.name;
//						std::cout << "Surname: "; std::cin >> obj.surname;
//						std::cout << "Patronymic: "; std::cin >> obj.patronymic;
//						std::cout << "Group: "; std::cin >> obj.groupCode;
//						std::cout << "Absent count: "; std::cin >> obj.absentCnt;
//						std::cout << "Average mark: "; std::cin >> obj.avgMark;
//						f.write((char *)&obj, sizeof(StudentData));
//					}
//				}
//				else if (type == CollegeData::fileType::LecturerFileBin) {
//					for (int i = 0; i < dataCount; i++) {
//						LecturerData obj;
//						std::cout << "\n\nEnter data for lecturer N" << i + 1 << std::endl;
//						std::cout << "Name: "; std::cin >> obj.name;
//						std::cout << "Surname: "; std::cin >> obj.surname;
//						std::cout << "Salary: "; std::cin >> obj.salary;
//						std::cout << "Group code where lecturer is class teacher: "; std::cin >> obj.classTeachedOf;
//						std::cout << "Groups where lecturer teaches (separated by ,): "; std::cin >> obj.lecturerIn;
//						std::cout << "Subjects that lecturer teaches (separated by ,): "; std::cin >> obj.lecturerSubjects;
//						f.write((char *)&obj, sizeof(LecturerData));
//					}
//				}
//				else if (type == CollegeData::fileType::GroupFileBin) {
//					for (int i = 0; i < dataCount; i++) {
//						GroupData obj;
//						std::cout << "\n\nEnter data for group N" << i + 1 << std::endl;
//						std::cout << "Group name: "; std::cin >> obj.groupName;
//						std::cout << "Class teacher: "; std::cin >> obj.classTeacher;
//						std::cout << "Group faculty: "; std::cin >> obj.groupFaculty;
//						std::cout << "Course of students: "; std::cin >> obj.studentsCourse;
//						std::cout << "Students count: "; std::cin >> obj.studentsCount;
//						f.write((char *)&obj, sizeof(GroupData));
//					}
//				}
//			}
//			else if (type == CollegeData::fileType::StudentFile ||
//				type == CollegeData::fileType::LecturerFile ||
//				type == CollegeData::fileType::GroupFile) {
//				f.open("./files directory/" + tmp, std::fstream::out | std::fstream::in | std::fstream::app);
//				if (type == CollegeData::fileType::StudentFile) {
//					for (int i = 0; i < dataCount; i++) {
//						std::string tempStr;
//						f << "{\n";
//						std::cout << "\n\nEnter data for student N" << i + 1 << std::endl;
//						std::cout << "Name: ";
//						std::cin >> tempStr;
//						f << "$name:" << tempStr << ";\n";
//						std::cout << "Surname: ";
//						std::cin >> tempStr;
//						f << "$surname:" << tempStr << ";\n";
//						std::cout << "Patronymic: ";
//						std::cin >> tempStr;
//						f << "$patronymic:" << tempStr << ";\n";
//						std::cout << "Group: ";
//						std::cin >> tempStr;
//						f << "$group:" << tempStr << ";\n";
//						std::cout << "Absent count: ";
//						std::cin >> tempStr;
//						f << "$absentCount:" << tempStr << ";\n";
//						std::cout << "Average mark: ";
//						std::cin >> tempStr;
//						f << "$avgMark:" << tempStr << ";\n";
//						f << "}\n";
//					}
//				}
//				else if (type == CollegeData::fileType::LecturerFile) {
//					for (int i = 0; i < dataCount; i++) {
//						std::string tempStr;
//						f << "{\n";
//						std::cout << "\n\nEnter data for lecturer N" << i + 1 << std::endl;
//						std::cout << "Name: ";
//						std::cin >> tempStr;
//						f << "$name:" << tempStr << ";\n";
//						std::cout << "Surname: ";
//						std::cin >> tempStr;
//						f << "$surname:" << tempStr << ";\n";
//						std::cout << "Salary: ";
//						std::cin >> tempStr;
//						f << "$salary:" << tempStr << ";\n";
//						std::cout << "Group code where lecturer is class teacher: ";
//						std::cin >> tempStr;
//						f << "$classTeacherOf:" << tempStr << ";\n";
//						std::cout << "Groups where lecturer teaches (separated by ,): ";
//						std::cin >> tempStr;
//						f << "$lecturerIn:" << tempStr << ";\n";
//						std::cout << "Subjects that lecturer teaches (separated by ,): ";
//						std::cin >> tempStr;
//						f << "$lecturerSubjects:" << tempStr << ";\n";
//						f << "}\n";
//					}
//				}
//				else if (type == CollegeData::fileType::GroupFile) {
//					for (int i = 0; i < dataCount; i++) {
//						std::string tempStr;
//						f << "{\n";
//						std::cout << "\n\nEnter data for group N" << i + 1 << std::endl;
//						std::cout << "Group name: ";
//						std::cin >> tempStr;
//						f << "$groupName:" << tempStr << ";\n";
//						std::cout << "Class teacher: ";
//						std::cin >> tempStr;
//						f << "$classTeacher:" << tempStr << ";\n";
//						std::cout << "Group faculty: ";
//						std::cin >> tempStr;
//						f << "$groupFaculty:" << tempStr << ";\n";
//						std::cout << "Course of students: ";
//						std::cin >> tempStr;
//						f << "$studentsCourse:" << tempStr << ";\n";
//						std::cout << "Students count: ";
//						std::cin >> tempStr;
//						f << "$studentsCount:" << tempStr << ";\n";
//						f << "}\n";
//					}
//				}
//			}
//			f.close();
//		}
//	}
//	else if (c == '4') {
//		std::string tmp;
//		do {
//			std::cout << "Enter file name (Can not contain /\\:*?\"<>|): ";
//			std::getline(std::cin, tmp);
//		} while (tmp.find('/') != std::string::npos || tmp.find('\\') != std::string::npos ||
//			tmp.find(':') != std::string::npos || tmp.find('*') != std::string::npos ||
//			tmp.find('?') != std::string::npos || tmp.find('"') != std::string::npos ||
//			tmp.find('<') != std::string::npos || tmp.find('>') != std::string::npos ||
//			tmp.find('|') != std::string::npos);
//		bool foundFile = false;
//		std::fstream f;
//		if (std::experimental::filesystem::exists("./files directory/" + tmp)) {
//			if (!std::experimental::filesystem::is_directory("./files directory/" + tmp)) {
//				std::string decision;
//				do {
//					std::cout << std::endl << "Are you sure you want to add data at selected index in selected file? (Y/N)" << std::endl;
//					std::cin >> decision;
//				} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//
//				if (decision == "Y" || decision == "y") {
//					f.open("./files directory/" + tmp, std::fstream::out | std::fstream::in);
//					foundFile = true;
//				}
//				else {
//					std::cout << std::endl << "Operation canceled." << std::endl;
//				}
//			}
//			else {
//				std::cout << std::endl << "Selected object is directory" << std::endl;
//			}
//		}
//		else {
//			std::cout << "No such file found!" << std::endl;
//		}
//		if (foundFile) {
//			std::cout << "Enter index: " << std::endl;
//			int index;
//			std::cin >> index;
//			CollegeData::fileType type;
//			f.read((char *)&type, sizeof(int));
//			if (f.is_open()) {
//				f.close();
//				f.clear();
//			}
//			if (type == CollegeData::fileType::StudentFile ||
//				type == CollegeData::fileType::LecturerFile ||
//				type == CollegeData::fileType::GroupFile) {
//				f.open("./files directory/" + tmp, std::fstream::out | std::fstream::in);
//				f.seekg(sizeof(int), std::ios::beg);
//				std::fstream tempFile("./files directory/A6864EB339B0E1F6E00D75293A8840ABF069A2C0FE82E6E53AF6AC099793C1D5.txt", std::fstream::out | std::fstream::trunc);
//				tempFile.write((char*)&type, sizeof(int));
//				tempFile << std::endl;
//				std::string line;
//				int currentInd = -1;
//				while (!f.eof()) {
//					std::getline(f, line);
//					if (line.find("{") != std::string::npos) {
//						++currentInd;
//					}
//					if (currentInd == index) {
//						if (type == CollegeData::fileType::StudentFile) {
//							std::string tempStr;
//							tempFile << "{\n";
//							std::cout << "\n\nEnter data for student" << std::endl;
//							std::cout << "Name: ";
//							std::cin >> tempStr;
//							tempFile << "$name:" << tempStr << ";\n";
//							std::cout << "Surname: ";
//							std::cin >> tempStr;
//							tempFile << "$surname:" << tempStr << ";\n";
//							std::cout << "Patronymic: ";
//							std::cin >> tempStr;
//							tempFile << "$patronymic:" << tempStr << ";\n";
//							std::cout << "Group: ";
//							std::cin >> tempStr;
//							tempFile << "$group:" << tempStr << ";\n";
//							std::cout << "Absent count: ";
//							std::cin >> tempStr;
//							tempFile << "$absentCount:" << tempStr << ";\n";
//							std::cout << "Average mark: ";
//							std::cin >> tempStr;
//							tempFile << "$avgMark:" << tempStr << ";\n";
//							tempFile << "}\n";
//						}
//						else if (type == CollegeData::fileType::LecturerFile) {
//							std::string tempStr;
//							tempFile << "{\n";
//							std::cout << "\n\nEnter data for lecturer" << std::endl;
//							std::cout << "Name: ";
//							std::cin >> tempStr;
//							tempFile << "$name:" << tempStr << ";\n";
//							std::cout << "Surname: ";
//							std::cin >> tempStr;
//							tempFile << "$surname:" << tempStr << ";\n";
//							std::cout << "Salary: ";
//							std::cin >> tempStr;
//							tempFile << "$salary:" << tempStr << ";\n";
//							std::cout << "Group code where lecturer is class teacher: ";
//							std::cin >> tempStr;
//							tempFile << "$classTeacherOf:" << tempStr << ";\n";
//							std::cout << "Groups where lecturer teaches (separated by ,): ";
//							std::cin >> tempStr;
//							tempFile << "$lecturerIn:" << tempStr << ";\n";
//							std::cout << "Subjects that lecturer teaches (separated by ,): ";
//							std::cin >> tempStr;
//							tempFile << "$lecturerSubjects:" << tempStr << ";\n";
//							tempFile << "}\n";
//						}
//						else if (type == CollegeData::fileType::GroupFile) {
//							std::string tempStr;
//							tempFile << "{\n";
//							std::cout << "\n\nEnter data for group" << std::endl;
//							std::cout << "Group name: ";
//							std::cin >> tempStr;
//							tempFile << "$groupName:" << tempStr << ";\n";
//							std::cout << "Class teacher: ";
//							std::cin >> tempStr;
//							tempFile << "$classTeacher:" << tempStr << ";\n";
//							std::cout << "Group faculty: ";
//							std::cin >> tempStr;
//							tempFile << "$groupFaculty:" << tempStr << ";\n";
//							std::cout << "Course of students: ";
//							std::cin >> tempStr;
//							tempFile << "$studentsCourse:" << tempStr << ";\n";
//							std::cout << "Students count: ";
//							std::cin >> tempStr;
//							tempFile << "$studentsCount:" << tempStr << ";\n";
//							tempFile << "}\n";
//						}
//						tempFile << line << std::endl;
//						++currentInd;
//					}
//					else {
//						tempFile << line << std::endl;
//					}
//				}
//				f.close();
//				f.clear();
//				tempFile.close();
//				tempFile.clear();
//				f.open("./files directory/" + tmp, std::fstream::out | std::fstream::trunc);
//				tempFile.open("./files directory/A6864EB339B0E1F6E00D75293A8840ABF069A2C0FE82E6E53AF6AC099793C1D5.txt", std::fstream::in);
//				while (!tempFile.eof()) {
//					std::getline(tempFile, line);
//					f << line << std::endl;
//				}
//				f.close();
//				tempFile.close();
//				std::remove("./files directory/A6864EB339B0E1F6E00D75293A8840ABF069A2C0FE82E6E53AF6AC099793C1D5.txt");
//			}
//			else if (type == CollegeData::fileType::StudentFileBin ||
//				type == CollegeData::fileType::LecturerFileBin ||
//				type == CollegeData::fileType::GroupFileBin) {
//				f.open("./files directory/" + tmp, std::fstream::out | std::fstream::in | std::fstream::binary);
//				f.seekg(sizeof(int), std::ios::beg);
//				std::vector<CollegeData*> fileData;
//				while (!f.eof() && f.good()) {
//					CollegeData *newObj;
//					if (type == CollegeData::fileType::StudentFileBin) {
//						newObj = new StudentData;
//						f.read((char*)newObj, sizeof(StudentData));
//					}
//					else if (type == CollegeData::fileType::LecturerFileBin) {
//						newObj = new LecturerData;
//						f.read((char*)newObj, sizeof(LecturerData));
//					}
//					else {
//						newObj = new GroupData;
//						f.read((char*)newObj, sizeof(GroupData));
//					}
//					if (!f.eof()) {
//						fileData.push_back(newObj);
//					}
//				}
//				f.close();
//				f.clear();
//				if (type == CollegeData::fileType::StudentFileBin) {
//					StudentData *obj = new StudentData;
//					std::cout << "\n\nEnter data for student" << std::endl;
//					std::cout << "Name: "; std::cin >> obj->name;
//					std::cout << "Surname: "; std::cin >> obj->surname;
//					std::cout << "Patronymic: "; std::cin >> obj->patronymic;
//					std::cout << "Group: "; std::cin >> obj->groupCode;
//					std::cout << "Absent count: "; std::cin >> obj->absentCnt;
//					std::cout << "Average mark: "; std::cin >> obj->avgMark;
//					fileData.insert(fileData.begin() + index, obj);
//				}
//				else if (type == CollegeData::fileType::LecturerFileBin) {
//					LecturerData *obj = new LecturerData;
//					std::cout << "\n\nEnter data for lecturer" << std::endl;
//					std::cout << "Name: "; std::cin >> obj->name;
//					std::cout << "Surname: "; std::cin >> obj->surname;
//					std::cout << "Salary: "; std::cin >> obj->salary;
//					std::cout << "Group code where lecturer is class teacher: "; std::cin >> obj->classTeachedOf;
//					std::cout << "Groups where lecturer teaches (separated by ,): "; std::cin >> obj->lecturerIn;
//					std::cout << "Subjects that lecturer teaches (separated by ,): "; std::cin >> obj->lecturerSubjects;
//					fileData.insert(fileData.begin() + index, obj);
//				}
//				else if (type == CollegeData::fileType::GroupFileBin) {
//					GroupData *obj = new GroupData;
//					std::cout << "\n\nEnter data for group" << std::endl;
//					std::cout << "Group name: "; std::cin >> obj->groupName;
//					std::cout << "Class teacher: "; std::cin >> obj->classTeacher;
//					std::cout << "Group faculty: "; std::cin >> obj->groupFaculty;
//					std::cout << "Course of students: "; std::cin >> obj->studentsCourse;
//					std::cout << "Students count: "; std::cin >> obj->studentsCount;
//					fileData.insert(fileData.begin() + index, obj);
//				}
//				f.open("./files directory/" + tmp, std::fstream::out | std::fstream::trunc | std::fstream::binary);
//				f.write((char *)&type, sizeof(int));
//				for (unsigned int ind = 0; ind < fileData.size(); ind++) {
//					if (type == CollegeData::fileType::StudentFileBin) {
//						f.write((char *)((StudentData*)fileData[ind]), sizeof(StudentData));
//					}
//					else if (type == CollegeData::fileType::LecturerFileBin) {
//						f.write((char *)((LecturerData*)fileData[ind]), sizeof(LecturerData));
//					}
//					else {
//						f.write((char *)((GroupData*)fileData[ind]), sizeof(GroupData));
//					}
//					delete fileData[ind];
//				}
//				f.close();
//			}
//		}
//	}
//	else if (c == '5') {
//		std::string tmp;
//		do {
//			std::cout << "Enter file name (Can not contain /\\:*?\"<>|): ";
//			std::getline(std::cin, tmp);
//		} while (tmp.find('/') != std::string::npos || tmp.find('\\') != std::string::npos ||
//			tmp.find(':') != std::string::npos || tmp.find('*') != std::string::npos ||
//			tmp.find('?') != std::string::npos || tmp.find('"') != std::string::npos ||
//			tmp.find('<') != std::string::npos || tmp.find('>') != std::string::npos ||
//			tmp.find('|') != std::string::npos);
//		bool fileNotFound = false;
//		std::fstream f;
//		if (!std::experimental::filesystem::exists("./files directory/" + tmp)) {
//			std::string decision;
//			do {
//				std::cout << std::endl << "Are you sure you want to create file and add data to it? (Y/N)" << std::endl;
//				std::cin >> decision;
//			} while (decision == "Y" && decision == "y" && decision == "N" && decision == "n");
//
//			if (decision == "Y" || decision == "y") {
//				fileNotFound = true;
//			}
//			else {
//				std::cout << std::endl << "Operation canceled." << std::endl;
//			}
//		}
//		else {
//			std::cout << "File already exists!" << std::endl;
//		}
//		if (fileNotFound) {
//			char decisionChr;
//			do {
//				std::cout << std::endl << "Select content type:" << std::endl
//					<< "0. Enter data for student," << std::endl
//					<< "1. Enter data for lecturer," << std::endl
//					<< "2. Enter data for group," << std::endl
//					<< "ESC. Exit." << std::endl;
//				decisionChr = _getch();
//				if (decisionChr == 27) {
//					std::string decision;
//					do
//					{
//						std::cout << std::endl << "Are you sure you want to exit? (Y/N)" << std::endl;
//						std::cin >> decision;
//					} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//					if (decision == "Y" || decision == "y") {
//						break;
//					}
//					else {
//						decisionChr = -32;
//						continue;
//					}
//				}
//			} while (decisionChr != '0' && decisionChr != '1' && decisionChr != '2');
//			char isBin;
//			if (decisionChr != 27) {
//				do {
//					std::cout << std::endl << "Select data type:" << std::endl
//						<< "0. Save as binary," << std::endl
//						<< "1. Save as ASCII," << std::endl
//						<< "ESC. Exit." << std::endl;
//					isBin = _getch();
//					if (isBin == 27) {
//						std::string decision;
//						do
//						{
//							std::cout << std::endl << "Are you sure you want to exit? (Y/N)" << std::endl;
//							std::cin >> decision;
//						} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//						if (decision == "Y" || decision == "y") {
//							break;
//						}
//						else {
//							isBin = -32;
//							continue;
//						}
//					}
//				} while (isBin != '0' && isBin != '1');
//				if (isBin != 27) {
//					std::cout << "Enter data count: ";
//					int dataCount;
//					std::cin >> dataCount;
//					if (isBin == '0') {
//						f.open("./files directory/" + tmp, std::fstream::out | std::fstream::trunc | std::fstream::binary);
//						if (decisionChr == '0') {
//							int classType = CollegeData::fileType::StudentFileBin;
//							f.write((char *)&classType, sizeof(int));
//							for (int i = 0; i < dataCount; i++) {
//								StudentData obj;
//								std::cout << "\n\nEnter data for student N" << i + 1 << std::endl;
//								std::cout << "Name: "; std::cin >> obj.name;
//								std::cout << "Surname: "; std::cin >> obj.surname;
//								std::cout << "Patronymic: "; std::cin >> obj.patronymic;
//								std::cout << "Group: "; std::cin >> obj.groupCode;
//								std::cout << "Absent count: "; std::cin >> obj.absentCnt;
//								std::cout << "Average mark: "; std::cin >> obj.avgMark;
//								f.write((char *)&obj, sizeof(StudentData));
//							}
//						}
//						else if (decisionChr == '1') {
//							int classType = CollegeData::fileType::LecturerFileBin;
//							f.write((char *)&classType, sizeof(classType));
//							for (int i = 0; i < dataCount; i++) {
//								LecturerData obj;
//								std::cout << "\n\nEnter data for lecturer N" << i + 1 << std::endl;
//								std::cout << "Name: "; std::cin >> obj.name;
//								std::cout << "Surname: "; std::cin >> obj.surname;
//								std::cout << "Salary: "; std::cin >> obj.salary;
//								std::cout << "Group code where lecturer is class teacher: "; std::cin >> obj.classTeachedOf;
//								std::cout << "Groups where lecturer teaches (separated by ,): "; std::cin >> obj.lecturerIn;
//								std::cout << "Subjects that lecturer teaches (separated by ,): "; std::cin >> obj.lecturerSubjects;
//								f.write((char *)&obj, sizeof(LecturerData));
//							}
//						}
//						else if (decisionChr == '2') {
//							int classType = CollegeData::fileType::GroupFileBin;
//							f.write((char *)&classType, sizeof(classType));
//							for (int i = 0; i < dataCount; i++) {
//								GroupData obj;
//								std::cout << "\n\nEnter data for group N" << i + 1 << std::endl;
//								std::cout << "Group name: "; std::cin >> obj.groupName;
//								std::cout << "Class teacher: "; std::cin >> obj.classTeacher;
//								std::cout << "Group faculty: "; std::cin >> obj.groupFaculty;
//								std::cout << "Course of students: "; std::cin >> obj.studentsCourse;
//								std::cout << "Students count: "; std::cin >> obj.studentsCount;
//								f.write((char *)&obj, sizeof(GroupData));
//							}
//						}
//					}
//					else {
//						f.open("./files directory/" + tmp, std::fstream::out | std::fstream::trunc);
//						if (decisionChr == '0') {
//							int classType = CollegeData::fileType::StudentFile;
//							f.write((char *)&classType, sizeof(classType));
//							f << std::endl;
//							for (int i = 0; i < dataCount; i++) {
//								std::string tempStr;
//								f << "{\n";
//								std::cout << "\n\nEnter data for student N" << i + 1 << std::endl;
//								std::cout << "Name: ";
//								std::cin >> tempStr;
//								f << "$name:" << tempStr << ";\n";
//								std::cout << "Surname: ";
//								std::cin >> tempStr;
//								f << "$surname:" << tempStr << ";\n";
//								std::cout << "Patronymic: ";
//								std::cin >> tempStr;
//								f << "$patronymic:" << tempStr << ";\n";
//								std::cout << "Group: ";
//								std::cin >> tempStr;
//								f << "$group:" << tempStr << ";\n";
//								std::cout << "Absent count: ";
//								std::cin >> tempStr;
//								f << "$absentCount:" << tempStr << ";\n";
//								std::cout << "Average mark: ";
//								std::cin >> tempStr;
//								f << "$avgMark:" << tempStr << ";\n";
//								f << "}\n";
//							}
//						}
//						else if (decisionChr == '1') {
//							int classType = CollegeData::fileType::LecturerFile;
//							f.write((char *)&classType, sizeof(classType));
//							f << std::endl;
//							for (int i = 0; i < dataCount; i++) {
//								std::string tempStr;
//								f << "{\n";
//								std::cout << "\n\nEnter data for lecturer N" << i + 1 << std::endl;
//								std::cout << "Name: ";
//								std::cin >> tempStr;
//								f << "$name:" << tempStr << ";\n";
//								std::cout << "Surname: ";
//								std::cin >> tempStr;
//								f << "$surname:" << tempStr << ";\n";
//								std::cout << "Salary: ";
//								std::cin >> tempStr;
//								f << "$salary:" << tempStr << ";\n";
//								std::cout << "Group code where lecturer is class teacher: ";
//								std::cin >> tempStr;
//								f << "$classTeacherOf:" << tempStr << ";\n";
//								std::cout << "Groups where lecturer teaches (separated by ,): ";
//								std::cin >> tempStr;
//								f << "$lecturerIn:" << tempStr << ";\n";
//								std::cout << "Subjects that lecturer teaches (separated by ,): ";
//								std::cin >> tempStr;
//								f << "$lecturerSubjects:" << tempStr << ";\n";
//								f << "}\n";
//							}
//						}
//						else if (decisionChr == '2') {
//							int classType = CollegeData::fileType::GroupFile;
//							f.write((char *)&classType, sizeof(classType));
//							f << std::endl;
//							for (int i = 0; i < dataCount; i++) {
//								std::string tempStr;
//								f << "{\n";
//								std::cout << "\n\nEnter data for group N" << i + 1 << std::endl;
//								std::cout << "Group name: ";
//								std::cin >> tempStr;
//								f << "$groupName:" << tempStr << ";\n";
//								std::cout << "Class teacher: ";
//								std::cin >> tempStr;
//								f << "$classTeacher:" << tempStr << ";\n";
//								std::cout << "Group faculty: ";
//								std::cin >> tempStr;
//								f << "$groupFaculty:" << tempStr << ";\n";
//								std::cout << "Course of students: ";
//								std::cin >> tempStr;
//								f << "$studentsCourse:" << tempStr << ";\n";
//								std::cout << "Students count: ";
//								std::cin >> tempStr;
//								f << "$studentsCount:" << tempStr << ";\n";
//								f << "}\n";
//							}
//						}
//					}
//					f.close();
//				}
//			}
//		}
//	}
//	else if (c == '6') {
//		std::string tmp;
//		do {
//			std::cout << "Enter file name (Can not contain /\\:*?\"<>|): ";
//			std::getline(std::cin, tmp);
//		} while (tmp.find('/') != std::string::npos || tmp.find('\\') != std::string::npos ||
//			tmp.find(':') != std::string::npos || tmp.find('*') != std::string::npos ||
//			tmp.find('?') != std::string::npos || tmp.find('"') != std::string::npos ||
//			tmp.find('<') != std::string::npos || tmp.find('>') != std::string::npos ||
//			tmp.find('|') != std::string::npos);
//		bool foundFile = false;
//		std::fstream f;
//		if (std::experimental::filesystem::exists("./files directory/" + tmp)) {
//			if (!std::experimental::filesystem::is_directory("./files directory/" + tmp)) {
//				std::string decision;
//				do {
//					std::cout << std::endl << "Are you sure you want to output all data from selected file? (Y/N)" << std::endl;
//					std::cin >> decision;
//				} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//
//				if (decision == "Y" || decision == "y") {
//					f.open("./files directory/" + tmp, std::fstream::in);
//					foundFile = true;
//				}
//				else {
//					std::cout << std::endl << "Operation canceled." << std::endl;
//				}
//			}
//			else {
//				std::cout << std::endl << "Selected object is directory" << std::endl;
//			}
//		}
//		else {
//			std::cout << "No such file found!" << std::endl;
//		}
//		if (foundFile) {
//			CollegeData::fileType type;
//			f.read((char *)&type, sizeof(int));
//			if (f.is_open()) {
//				f.close();
//				f.clear();
//			}
//			std::vector<CollegeData*> fileData;
//			if (type == CollegeData::fileType::StudentFile ||
//				type == CollegeData::fileType::LecturerFile ||
//				type == CollegeData::fileType::GroupFile) {
//				f.open("./files directory/" + tmp, std::fstream::in);
//				f.seekg(sizeof(int), std::ios::beg);
//				std::string line;
//				while (!f.eof()) {
//					std::getline(f, line);
//					if (type == CollegeData::fileType::StudentFile) {
//						if (line.find("{") != std::string::npos) {
//							fileData.push_back(new StudentData);
//						}
//						int pos;
//						if ((pos = line.find("$name:")) != std::string::npos) {
//							strcpy_s(((StudentData*)fileData.back())->name, line.substr(pos + 6, line.length() - 7 - pos).c_str());
//						}
//						else if ((pos = line.find("$surname:")) != std::string::npos) {
//							strcpy_s(((StudentData*)fileData.back())->surname, line.substr(pos + 9, line.length() - 10 - pos).c_str());
//						}
//						else if ((pos = line.find("$patronymic:")) != std::string::npos) {
//							strcpy_s(((StudentData*)fileData.back())->patronymic, line.substr(pos + 12, line.length() - 13 - pos).c_str());
//						}
//						else if ((pos = line.find("$group:")) != std::string::npos) {
//							strcpy_s(((StudentData*)fileData.back())->groupCode, line.substr(pos + 7, line.length() - 8 - pos).c_str());
//						}
//						else if ((pos = line.find("$absentCount:")) != std::string::npos) {
//							((StudentData*)fileData.back())->absentCnt = atoi(line.substr(pos + 13, line.length() - 14 - pos).c_str());
//						}
//						else if ((pos = line.find("$avgMark:")) != std::string::npos) {
//							((StudentData*)fileData.back())->avgMark = (float)atof(line.substr(pos + 9, line.length() - 10 - pos).c_str());
//						}
//					}
//					else if (type == CollegeData::fileType::LecturerFile) {
//						if (line.find("{") != std::string::npos) {
//							fileData.push_back(new LecturerData);
//						}
//						int pos;
//						if ((pos = line.find("$name:")) != std::string::npos) {
//							strcpy_s(((LecturerData*)fileData.back())->name, line.substr(pos + 6, line.length() - 7 - pos).c_str());
//						}
//						else if ((pos = line.find("$surname:")) != std::string::npos) {
//							strcpy_s(((LecturerData*)fileData.back())->surname, line.substr(pos + 9, line.length() - 10 - pos).c_str());
//						}
//						else if ((pos = line.find("$salary:")) != std::string::npos) {
//							((LecturerData*)fileData.back())->salary = atoi(line.substr(pos + 12, line.length() - 13 - pos).c_str());
//						}
//						else if ((pos = line.find("$classTeacherOf:")) != std::string::npos) {
//							strcpy_s(((LecturerData*)fileData.back())->classTeachedOf, line.substr(pos + 16, line.length() - 17 - pos).c_str());
//						}
//						else if ((pos = line.find("$lecturerIn:")) != std::string::npos) {
//							strcpy_s(((LecturerData*)fileData.back())->lecturerIn, line.substr(pos + 12, line.length() - 13 - pos).c_str());
//						}
//						else if ((pos = line.find("$lecturerSubjects:")) != std::string::npos) {
//							strcpy_s(((LecturerData*)fileData.back())->lecturerSubjects, line.substr(pos + 9, line.length() - 10 - pos).c_str());
//						}
//					}
//					else if (type == CollegeData::fileType::GroupFile) {
//						if (line.find("{") != std::string::npos) {
//							fileData.push_back(new GroupData);
//						}
//						int pos;
//						if ((pos = line.find("$groupName:")) != std::string::npos) {
//							strcpy_s(((GroupData*)fileData.back())->groupName, line.substr(pos + 11, line.length() - 12 - pos).c_str());
//						}
//						else if ((pos = line.find("$classTeacher:")) != std::string::npos) {
//							strcpy_s(((GroupData*)fileData.back())->classTeacher, line.substr(pos + 14, line.length() - 15 - pos).c_str());
//						}
//						else if ((pos = line.find("$groupFaculty:")) != std::string::npos) {
//							strcpy_s(((GroupData*)fileData.back())->groupFaculty, line.substr(pos + 14, line.length() - 15 - pos).c_str());
//						}
//						else if ((pos = line.find("$studentsCourse:")) != std::string::npos) {
//							((GroupData*)fileData.back())->studentsCourse = atoi(line.substr(pos + 16, line.length() - 17 - pos).c_str());
//						}
//						else if ((pos = line.find("$studentsCount:")) != std::string::npos) {
//							((GroupData*)fileData.back())->studentsCount = atoi(line.substr(pos + 15, line.length() - 16 - pos).c_str());
//						}
//					}
//				}
//				f.close();
//			}
//			else if (type == CollegeData::fileType::StudentFileBin ||
//				type == CollegeData::fileType::LecturerFileBin ||
//				type == CollegeData::fileType::GroupFileBin) {
//				f.open("./files directory/" + tmp, std::fstream::in | std::fstream::binary);
//				f.seekg(sizeof(int), std::ios::beg);
//				while (!f.eof() && f.good()) {
//					CollegeData *newObj;
//					if (type == CollegeData::fileType::StudentFileBin) {
//						newObj = new StudentData;
//						f.read((char*)newObj, sizeof(StudentData));
//					}
//					else if (type == CollegeData::fileType::LecturerFileBin) {
//						newObj = new LecturerData;
//						f.read((char*)newObj, sizeof(LecturerData));
//					}
//					else {
//						newObj = new GroupData;
//						f.read((char*)newObj, sizeof(GroupData));
//					}
//					if (!f.eof()) {
//						fileData.push_back(newObj);
//					}
//				}
//				f.close();
//			}
//			int dataLength = fileData.size();
//			if (type == CollegeData::fileType::StudentFileBin ||
//				type == CollegeData::fileType::StudentFile) {
//				for (int i = 0; i < dataLength; i++) {
//					std::cout << "\n\nData of student N" << i + 1 << std::endl;
//					std::cout << "Name: ";
//					std::cout << ((StudentData*)fileData[i])->name << std::endl;
//					std::cout << "Surname: ";
//					std::cout << ((StudentData*)fileData[i])->surname << std::endl;
//					std::cout << "Patronymic: ";
//					std::cout << ((StudentData*)fileData[i])->patronymic << std::endl;
//					std::cout << "Group: ";
//					std::cout << ((StudentData*)fileData[i])->groupCode << std::endl;
//					std::cout << "Absent count: ";
//					std::cout << ((StudentData*)fileData[i])->absentCnt << std::endl;
//					std::cout << "Average mark: ";
//					std::cout << ((StudentData*)fileData[i])->avgMark << std::endl;
//					delete fileData[i];
//				}
//			}
//			else if (type == CollegeData::fileType::LecturerFileBin ||
//				type == CollegeData::fileType::LecturerFile) {
//				for (int i = 0; i < dataLength; i++) {
//					std::cout << "\n\nData of lecturer N" << i + 1 << std::endl;
//					std::cout << "Name: ";
//					std::cout << ((LecturerData*)fileData[i])->name << std::endl;
//					std::cout << "Surname: ";
//					std::cout << ((LecturerData*)fileData[i])->surname << std::endl;
//					std::cout << "Salary: ";
//					std::cout << ((LecturerData*)fileData[i])->salary << std::endl;
//					std::cout << "Group code where lecturer is class teacher: ";
//					std::cout << ((LecturerData*)fileData[i])->classTeachedOf << std::endl;
//					std::cout << "Groups where lecturer teaches (separated by ,): ";
//					std::cout << ((LecturerData*)fileData[i])->lecturerIn << std::endl;
//					std::cout << "Subjects that lecturer teaches (separated by ,): ";
//					std::cout << ((LecturerData*)fileData[i])->lecturerSubjects << std::endl;
//					delete fileData[i];
//				}
//			}
//			else if (type == CollegeData::fileType::GroupFileBin ||
//				type == CollegeData::fileType::GroupFile) {
//				for (int i = 0; i < dataLength; i++) {
//					std::cout << "\n\nData of group N" << i + 1 << std::endl;
//					std::cout << "Group name: ";
//					std::cout << ((GroupData*)fileData[i])->groupName << std::endl;
//					std::cout << "Class teacher: ";
//					std::cout << ((GroupData*)fileData[i])->classTeacher << std::endl;
//					std::cout << "Group faculty: ";
//					std::cout << ((GroupData*)fileData[i])->groupFaculty << std::endl;
//					std::cout << "Course of students: ";
//					std::cout << ((GroupData*)fileData[i])->studentsCourse << std::endl;
//					std::cout << "Students count: ";
//					std::cout << ((GroupData*)fileData[i])->studentsCount << std::endl;
//					delete fileData[i];
//				}
//			}
//		}
//	}
//	else if (c == '7') {
//		std::string tmp;
//		do {
//			std::cout << "Enter file name (Can not contain /\\:*?\"<>|): ";
//			std::getline(std::cin, tmp);
//		} while (tmp.find('/') != std::string::npos || tmp.find('\\') != std::string::npos ||
//			tmp.find(':') != std::string::npos || tmp.find('*') != std::string::npos ||
//			tmp.find('?') != std::string::npos || tmp.find('"') != std::string::npos ||
//			tmp.find('<') != std::string::npos || tmp.find('>') != std::string::npos ||
//			tmp.find('|') != std::string::npos);
//		bool foundFile = false;
//		std::fstream f;
//		if (std::experimental::filesystem::exists("./files directory/" + tmp)) {
//			if (!std::experimental::filesystem::is_directory("./files directory/" + tmp)) {
//				std::string decision;
//				do {
//					std::cout << std::endl << "Are you sure you want to output data on selected index from selected file? (Y/N)" << std::endl;
//					std::cin >> decision;
//				} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//
//				if (decision == "Y" || decision == "y") {
//					f.open("./files directory/" + tmp, std::fstream::in);
//					foundFile = true;
//				}
//				else {
//					std::cout << std::endl << "Operation canceled." << std::endl;
//				}
//			}
//			else {
//				std::cout << std::endl << "Selected object is directory" << std::endl;
//			}
//		}
//		else {
//			std::cout << "No such file found!" << std::endl;
//		}
//		if (foundFile) {
//			std::cout << "Enter index: " << std::endl;
//			int index;
//			std::cin >> index;
//			CollegeData::fileType type;
//			f.read((char *)&type, sizeof(int));
//			if (f.is_open()) {
//				f.close();
//				f.clear();
//			}
//			CollegeData * objFound = new CollegeData;
//			bool indexFound = false;
//			if (type == CollegeData::fileType::StudentFile ||
//				type == CollegeData::fileType::LecturerFile ||
//				type == CollegeData::fileType::GroupFile) {
//				f.open("./files directory/" + tmp, std::fstream::in);
//				f.seekg(sizeof(int), std::ios::beg);
//				std::string line;
//				int currentInd = -1;
//				while (!f.eof()) {
//					std::getline(f, line);
//					if (line.find("{") != std::string::npos) {
//						++currentInd;
//					}
//					if (currentInd > index) {
//						break;
//					}
//					if (currentInd == index) {
//						if (type == CollegeData::fileType::StudentFile) {
//							if (!indexFound) {
//								indexFound = true;
//								delete objFound;
//								objFound = new StudentData;
//							}
//							int pos;
//							if ((pos = line.find("$name:")) != std::string::npos) {
//								strcpy_s(((StudentData*)objFound)->name, line.substr(pos + 6, line.length() - 7 - pos).c_str());
//							}
//							else if ((pos = line.find("$surname:")) != std::string::npos) {
//								strcpy_s(((StudentData*)objFound)->surname, line.substr(pos + 9, line.length() - 10 - pos).c_str());
//							}
//							else if ((pos = line.find("$patronymic:")) != std::string::npos) {
//								strcpy_s(((StudentData*)objFound)->patronymic, line.substr(pos + 12, line.length() - 13 - pos).c_str());
//							}
//							else if ((pos = line.find("$group:")) != std::string::npos) {
//								strcpy_s(((StudentData*)objFound)->groupCode, line.substr(pos + 7, line.length() - 8 - pos).c_str());
//							}
//							else if ((pos = line.find("$absentCount:")) != std::string::npos) {
//								((StudentData*)objFound)->absentCnt = atoi(line.substr(pos + 13, line.length() - 14 - pos).c_str());
//							}
//							else if ((pos = line.find("$avgMark:")) != std::string::npos) {
//								((StudentData*)objFound)->avgMark = (float)atof(line.substr(pos + 9, line.length() - 10 - pos).c_str());
//							}
//						}
//						else if (type == CollegeData::fileType::LecturerFile) {
//							if (!indexFound) {
//								indexFound = true;
//								delete objFound;
//								objFound = new LecturerData;
//							}
//							int pos;
//							if ((pos = line.find("$name:")) != std::string::npos) {
//								strcpy_s(((LecturerData*)objFound)->name, line.substr(pos + 6, line.length() - 7 - pos).c_str());
//							}
//							else if ((pos = line.find("$surname:")) != std::string::npos) {
//								strcpy_s(((LecturerData*)objFound)->surname, line.substr(pos + 9, line.length() - 10 - pos).c_str());
//							}
//							else if ((pos = line.find("$salary:")) != std::string::npos) {
//								((LecturerData*)objFound)->salary = atoi(line.substr(pos + 12, line.length() - 13 - pos).c_str());
//							}
//							else if ((pos = line.find("$classTeacherOf:")) != std::string::npos) {
//								strcpy_s(((LecturerData*)objFound)->classTeachedOf, line.substr(pos + 16, line.length() - 17 - pos).c_str());
//							}
//							else if ((pos = line.find("$lecturerIn:")) != std::string::npos) {
//								strcpy_s(((LecturerData*)objFound)->lecturerIn, line.substr(pos + 12, line.length() - 13 - pos).c_str());
//							}
//							else if ((pos = line.find("$lecturerSubjects:")) != std::string::npos) {
//								strcpy_s(((LecturerData*)objFound)->lecturerSubjects, line.substr(pos + 9, line.length() - 10 - pos).c_str());
//							}
//						}
//						else if (type == CollegeData::fileType::GroupFile) {
//							if (!indexFound) {
//								indexFound = true;
//								delete objFound;
//								objFound = new GroupData;
//							}
//							int pos;
//							if ((pos = line.find("$groupName:")) != std::string::npos) {
//								strcpy_s(((GroupData*)objFound)->groupName, line.substr(pos + 11, line.length() - 12 - pos).c_str());
//							}
//							else if ((pos = line.find("$classTeacher:")) != std::string::npos) {
//								strcpy_s(((GroupData*)objFound)->classTeacher, line.substr(pos + 14, line.length() - 15 - pos).c_str());
//							}
//							else if ((pos = line.find("$groupFaculty:")) != std::string::npos) {
//								strcpy_s(((GroupData*)objFound)->groupFaculty, line.substr(pos + 14, line.length() - 15 - pos).c_str());
//							}
//							else if ((pos = line.find("$studentsCourse:")) != std::string::npos) {
//								((GroupData*)objFound)->studentsCourse = atoi(line.substr(pos + 16, line.length() - 17 - pos).c_str());
//							}
//							else if ((pos = line.find("$studentsCount:")) != std::string::npos) {
//								((GroupData*)objFound)->studentsCount = atoi(line.substr(pos + 15, line.length() - 16 - pos).c_str());
//							}
//						}
//					}
//				}
//			}
//			else if (type == CollegeData::fileType::StudentFileBin ||
//				type == CollegeData::fileType::LecturerFileBin ||
//				type == CollegeData::fileType::GroupFileBin) {
//				f.open("./files directory/" + tmp, std::fstream::in | std::fstream::binary);
//				f.seekg(sizeof(int), std::ios::beg);
//				int currentInd = -1;
//				if (type == CollegeData::fileType::StudentFileBin) {
//					delete objFound;
//					objFound = new StudentData;
//				}
//				else if (type == CollegeData::fileType::LecturerFileBin) {
//					delete objFound;
//					objFound = new LecturerData;
//				}
//				else {
//					delete objFound;
//					objFound = new GroupData;
//				}
//				while (!f.eof() && f.good()) {
//					if (currentInd > index) {
//						break;
//					}
//					if (type == CollegeData::fileType::StudentFileBin) {
//						f.read((char*)objFound, sizeof(StudentData));
//					}
//					else if (type == CollegeData::fileType::LecturerFileBin) {
//						f.read((char*)objFound, sizeof(LecturerData));
//					}
//					else if (type == CollegeData::fileType::GroupFileBin) {
//						f.read((char*)objFound, sizeof(GroupData));
//					}
//					if (!f.eof()) {
//						++currentInd;
//					}
//					if (currentInd == index) {
//						indexFound = true;
//						break;
//					}
//				}
//			}
//			else {
//				std::cout << "Can't get file type!" << std::endl;
//			}
//			f.close();
//			if (indexFound) {
//				if (type == CollegeData::fileType::StudentFileBin ||
//					type == CollegeData::fileType::StudentFile) {
//					std::cout << "\n\nData of student on index " << index << std::endl;
//					std::cout << "Name: ";
//					std::cout << ((StudentData*)objFound)->name << std::endl;
//					std::cout << "Surname: ";
//					std::cout << ((StudentData*)objFound)->surname << std::endl;
//					std::cout << "Patronymic: ";
//					std::cout << ((StudentData*)objFound)->patronymic << std::endl;
//					std::cout << "Group: ";
//					std::cout << ((StudentData*)objFound)->groupCode << std::endl;
//					std::cout << "Absent count: ";
//					std::cout << ((StudentData*)objFound)->absentCnt << std::endl;
//					std::cout << "Average mark: ";
//					std::cout << ((StudentData*)objFound)->avgMark << std::endl;
//					delete objFound;
//				}
//				else if (type == CollegeData::fileType::LecturerFileBin ||
//					type == CollegeData::fileType::LecturerFile) {
//					std::cout << "\n\nData of lecturer on index " << index << std::endl;
//					std::cout << "Name: ";
//					std::cout << ((LecturerData*)objFound)->name << std::endl;
//					std::cout << "Surname: ";
//					std::cout << ((LecturerData*)objFound)->surname << std::endl;
//					std::cout << "Salary: ";
//					std::cout << ((LecturerData*)objFound)->salary << std::endl;
//					std::cout << "Group code where lecturer is class teacher: ";
//					std::cout << ((LecturerData*)objFound)->classTeachedOf << std::endl;
//					std::cout << "Groups where lecturer teaches (separated by ,): ";
//					std::cout << ((LecturerData*)objFound)->lecturerIn << std::endl;
//					std::cout << "Subjects that lecturer teaches (separated by ,): ";
//					std::cout << ((LecturerData*)objFound)->lecturerSubjects << std::endl;
//					delete objFound;
//				}
//				else if (type == CollegeData::fileType::GroupFileBin ||
//					type == CollegeData::fileType::GroupFile) {
//					std::cout << "\n\nData of group on index " << index << std::endl;
//					std::cout << "Group name: ";
//					std::cout << ((GroupData*)objFound)->groupName << std::endl;
//					std::cout << "Class teacher: ";
//					std::cout << ((GroupData*)objFound)->classTeacher << std::endl;
//					std::cout << "Group faculty: ";
//					std::cout << ((GroupData*)objFound)->groupFaculty << std::endl;
//					std::cout << "Course of students: ";
//					std::cout << ((GroupData*)objFound)->studentsCourse << std::endl;
//					std::cout << "Students count: ";
//					std::cout << ((GroupData*)objFound)->studentsCount << std::endl;
//					delete objFound;
//				}
//			}
//		}
//	}
//	else if (c == '8') {
//		std::string tmp;
//		do {
//			std::cout << "Enter file name (Can not contain /\\:*?\"<>|): ";
//			std::getline(std::cin, tmp);
//		} while (tmp.find('/') != std::string::npos || tmp.find('\\') != std::string::npos ||
//			tmp.find(':') != std::string::npos || tmp.find('*') != std::string::npos ||
//			tmp.find('?') != std::string::npos || tmp.find('"') != std::string::npos ||
//			tmp.find('<') != std::string::npos || tmp.find('>') != std::string::npos ||
//			tmp.find('|') != std::string::npos);
//		bool foundFile = false;
//		std::fstream f;
//		if (std::experimental::filesystem::exists("./files directory/" + tmp)) {
//			if (!std::experimental::filesystem::is_directory("./files directory/" + tmp)) {
//				std::string decision;
//				do {
//					std::cout << std::endl << "Are you sure you want to output data on selected index from selected file? (Y/N)" << std::endl;
//					std::cin >> decision;
//				} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//
//				if (decision == "Y" || decision == "y") {
//					f.open("./files directory/" + tmp, std::fstream::in);
//					foundFile = true;
//				}
//				else {
//					std::cout << std::endl << "Operation canceled." << std::endl;
//				}
//			}
//			else {
//				std::cout << std::endl << "Selected object is directory" << std::endl;
//			}
//		}
//		else {
//			std::cout << "No such file found!" << std::endl;
//		}
//		if (foundFile) {
//			std::cout << "Enter index: " << std::endl;
//			int index;
//			std::cin >> index;
//			CollegeData::fileType type;
//			f.read((char *)&type, sizeof(int));
//			if (f.is_open()) {
//				f.close();
//				f.clear();
//			}
//			std::vector<CollegeData*> fileData;
//			if (type == CollegeData::fileType::StudentFile ||
//				type == CollegeData::fileType::LecturerFile ||
//				type == CollegeData::fileType::GroupFile) {
//				f.open("./files directory/" + tmp, std::fstream::in);
//				f.seekg(sizeof(int), std::ios::beg);
//				std::string line;
//				while (!f.eof()) {
//					std::getline(f, line);
//					if (type == CollegeData::fileType::StudentFile) {
//						if (line.find("{") != std::string::npos) {
//							fileData.push_back(new StudentData);
//						}
//						int pos;
//						if ((pos = line.find("$name:")) != std::string::npos) {
//							strcpy_s(((StudentData*)fileData.back())->name, line.substr(pos + 6, line.length() - 7 - pos).c_str());
//						}
//						else if ((pos = line.find("$surname:")) != std::string::npos) {
//							strcpy_s(((StudentData*)fileData.back())->surname, line.substr(pos + 9, line.length() - 10 - pos).c_str());
//						}
//						else if ((pos = line.find("$patronymic:")) != std::string::npos) {
//							strcpy_s(((StudentData*)fileData.back())->patronymic, line.substr(pos + 12, line.length() - 13 - pos).c_str());
//						}
//						else if ((pos = line.find("$group:")) != std::string::npos) {
//							strcpy_s(((StudentData*)fileData.back())->groupCode, line.substr(pos + 7, line.length() - 8 - pos).c_str());
//						}
//						else if ((pos = line.find("$absentCount:")) != std::string::npos) {
//							((StudentData*)fileData.back())->absentCnt = atoi(line.substr(pos + 13, line.length() - 14 - pos).c_str());
//						}
//						else if ((pos = line.find("$avgMark:")) != std::string::npos) {
//							((StudentData*)fileData.back())->avgMark = (float)atof(line.substr(pos + 9, line.length() - 10 - pos).c_str());
//						}
//					}
//					else if (type == CollegeData::fileType::LecturerFile) {
//						if (line.find("{") != std::string::npos) {
//							fileData.push_back(new LecturerData);
//						}
//						int pos;
//						if ((pos = line.find("$name:")) != std::string::npos) {
//							strcpy_s(((LecturerData*)fileData.back())->name, line.substr(pos + 6, line.length() - 7 - pos).c_str());
//						}
//						else if ((pos = line.find("$surname:")) != std::string::npos) {
//							strcpy_s(((LecturerData*)fileData.back())->surname, line.substr(pos + 9, line.length() - 10 - pos).c_str());
//						}
//						else if ((pos = line.find("$salary:")) != std::string::npos) {
//							((LecturerData*)fileData.back())->salary = atoi(line.substr(pos + 12, line.length() - 13 - pos).c_str());
//						}
//						else if ((pos = line.find("$classTeacherOf:")) != std::string::npos) {
//							strcpy_s(((LecturerData*)fileData.back())->classTeachedOf, line.substr(pos + 16, line.length() - 17 - pos).c_str());
//						}
//						else if ((pos = line.find("$lecturerIn:")) != std::string::npos) {
//							strcpy_s(((LecturerData*)fileData.back())->lecturerIn, line.substr(pos + 12, line.length() - 13 - pos).c_str());
//						}
//						else if ((pos = line.find("$lecturerSubjects:")) != std::string::npos) {
//							strcpy_s(((LecturerData*)fileData.back())->lecturerSubjects, line.substr(pos + 9, line.length() - 10 - pos).c_str());
//						}
//					}
//					else if (type == CollegeData::fileType::GroupFile) {
//						if (line.find("{") != std::string::npos) {
//							fileData.push_back(new GroupData);
//						}
//						int pos;
//						if ((pos = line.find("$groupName:")) != std::string::npos) {
//							strcpy_s(((GroupData*)fileData.back())->groupName, line.substr(pos + 11, line.length() - 12 - pos).c_str());
//						}
//						else if ((pos = line.find("$classTeacher:")) != std::string::npos) {
//							strcpy_s(((GroupData*)fileData.back())->classTeacher, line.substr(pos + 14, line.length() - 15 - pos).c_str());
//						}
//						else if ((pos = line.find("$groupFaculty:")) != std::string::npos) {
//							strcpy_s(((GroupData*)fileData.back())->groupFaculty, line.substr(pos + 14, line.length() - 15 - pos).c_str());
//						}
//						else if ((pos = line.find("$studentsCourse:")) != std::string::npos) {
//							((GroupData*)fileData.back())->studentsCourse = atoi(line.substr(pos + 16, line.length() - 17 - pos).c_str());
//						}
//						else if ((pos = line.find("$studentsCount:")) != std::string::npos) {
//							((GroupData*)fileData.back())->studentsCount = atoi(line.substr(pos + 15, line.length() - 16 - pos).c_str());
//						}
//					}
//				}
//				f.close();
//			}
//			else if (type == CollegeData::fileType::StudentFileBin ||
//				type == CollegeData::fileType::LecturerFileBin ||
//				type == CollegeData::fileType::GroupFileBin) {
//				f.open("./files directory/" + tmp, std::fstream::in | std::fstream::binary);
//				f.seekg(sizeof(int), std::ios::beg);
//				while (!f.eof() && f.good()) {
//					CollegeData *newObj;
//					if (type == CollegeData::fileType::StudentFileBin) {
//						newObj = new StudentData;
//						f.read((char*)newObj, sizeof(StudentData));
//					}
//					else if (type == CollegeData::fileType::LecturerFileBin) {
//						newObj = new LecturerData;
//						f.read((char*)newObj, sizeof(LecturerData));
//					}
//					else {
//						newObj = new GroupData;
//						f.read((char*)newObj, sizeof(GroupData));
//					}
//					if (!f.eof()) {
//						fileData.push_back(newObj);
//					}
//				}
//				f.close();
//			}
//			int dataLength = fileData.size();
//			if (index >= 0 && index < dataLength) {
//				if (type == CollegeData::fileType::StudentFileBin ||
//					type == CollegeData::fileType::StudentFile) {
//					fileData[index] = new StudentData;
//					std::cout << "\n\nEnter data for student on index " << index << std::endl;
//					std::cout << "Name: "; std::cin >> ((StudentData*)fileData[index])->name;
//					std::cout << "Surname: "; std::cin >> ((StudentData*)fileData[index])->surname;
//					std::cout << "Patronymic: "; std::cin >> ((StudentData*)fileData[index])->patronymic;
//					std::cout << "Group: "; std::cin >> ((StudentData*)fileData[index])->groupCode;
//					std::cout << "Absent count: "; std::cin >> ((StudentData*)fileData[index])->absentCnt;
//					std::cout << "Average mark: "; std::cin >> ((StudentData*)fileData[index])->avgMark;
//				}
//				else if (type == CollegeData::fileType::LecturerFileBin ||
//					type == CollegeData::fileType::LecturerFile) {
//					fileData[index] = new LecturerData;
//					std::cout << "\n\nEnter data for lecturer on index " << index << std::endl;
//					std::cout << "Name: ";
//					std::cin >> ((LecturerData*)fileData[index])->name;
//					std::cout << "Surname: ";
//					std::cin >> ((LecturerData*)fileData[index])->surname;
//					std::cout << "Salary: ";
//					std::cin >> ((LecturerData*)fileData[index])->salary;
//					std::cout << "Group code where lecturer is class teacher: ";
//					std::cin >> ((LecturerData*)fileData[index])->classTeachedOf;
//					std::cout << "Groups where lecturer teaches (separated by ,): ";
//					std::cin >> ((LecturerData*)fileData[index])->lecturerIn;
//					std::cout << "Subjects that lecturer teaches (separated by ,): ";
//					std::cin >> ((LecturerData*)fileData[index])->lecturerSubjects;
//				}
//				else if (type == CollegeData::fileType::GroupFileBin ||
//					type == CollegeData::fileType::GroupFile) {
//					fileData[index] = new GroupData;
//					std::cout << "\n\nEnter data for group on index " << index << std::endl;
//					std::cout << "Group name: "; std::cin >> ((GroupData*)fileData[index])->groupName;
//					std::cout << "Class teacher: "; std::cin >> ((GroupData*)fileData[index])->classTeacher;
//					std::cout << "Group faculty: "; std::cin >> ((GroupData*)fileData[index])->groupFaculty;
//					std::cout << "Course of students: "; std::cin >> ((GroupData*)fileData[index])->studentsCourse;
//					std::cout << "Students count: "; std::cin >> ((GroupData*)fileData[index])->studentsCount;
//				}
//
//				if (type == CollegeData::fileType::StudentFileBin ||
//					type == CollegeData::fileType::LecturerFileBin ||
//					type == CollegeData::fileType::GroupFileBin) {
//					f.open("./files directory/" + tmp, std::fstream::out | std::fstream::trunc | std::fstream::binary);
//					f.write((char *)&type, sizeof(int));
//					for (int i = 0; i < dataLength; i++) {
//						if (type == CollegeData::fileType::StudentFileBin) {
//							f.write((char *)((StudentData*)fileData[i]), sizeof(StudentData));
//						}
//						else if (type == CollegeData::fileType::LecturerFileBin) {
//							f.write((char *)((LecturerData*)fileData[i]), sizeof(LecturerData));
//						}
//						else {
//							f.write((char *)((GroupData*)fileData[i]), sizeof(GroupData));
//						}
//					}
//
//				}
//				else if (type == CollegeData::fileType::StudentFile ||
//					type == CollegeData::fileType::LecturerFile ||
//					type == CollegeData::fileType::GroupFile) {
//					f.open("./files directory/" + tmp, std::fstream::out | std::fstream::trunc);
//					f.write((char *)&type, sizeof(int));
//					f << std::endl;
//					for (int i = 0; i < dataLength; i++) {
//						if (type == CollegeData::fileType::StudentFile) {
//							f << "{\n";
//							f << "$name:" << ((StudentData*)fileData[i])->name << ";\n";
//							f << "$surname:" << ((StudentData*)fileData[i])->surname << ";\n";
//							f << "$patronymic:" << ((StudentData*)fileData[i])->patronymic << ";\n";
//							f << "$group:" << ((StudentData*)fileData[i])->groupCode << ";\n";
//							f << "$absentCount:" << ((StudentData*)fileData[i])->absentCnt << ";\n";
//							f << "$avgMark:" << ((StudentData*)fileData[i])->avgMark << ";\n";
//							f << "}\n";
//						}
//						else if (type == CollegeData::fileType::LecturerFile) {
//							f << "{\n";
//							f << "$name:" << ((LecturerData*)fileData[i])->name << ";\n";
//							f << "$surname:" << ((LecturerData*)fileData[i])->surname << ";\n";
//							f << "$salary:" << ((LecturerData*)fileData[i])->salary << ";\n";
//							f << "$classTeacherOf:" << ((LecturerData*)fileData[i])->classTeachedOf << ";\n";
//							f << "$lecturerIn:" << ((LecturerData*)fileData[i])->lecturerIn << ";\n";
//							f << "$lecturerSubjects:" << ((LecturerData*)fileData[i])->lecturerSubjects << ";\n";
//							f << "}\n";
//						}
//						else if (type == CollegeData::fileType::GroupFile) {
//							f << "{\n";
//							f << "$groupName:" << ((GroupData*)fileData[i])->groupName << ";\n";
//							f << "$classTeacher:" << ((GroupData*)fileData[i])->classTeacher << ";\n";
//							f << "$groupFaculty:" << ((GroupData*)fileData[i])->groupFaculty << ";\n";
//							f << "$studentsCourse:" << ((GroupData*)fileData[i])->studentsCourse << ";\n";
//							f << "$studentsCount:" << ((GroupData*)fileData[i])->studentsCount << ";\n";
//							f << "}\n";
//						}
//					}
//				}
//			}
//		}
//	}
//	else if (c == '9') {
//		std::string tmp;
//		do {
//			std::cout << "Enter file name (Can not contain /\\:*?\"<>|): ";
//			std::getline(std::cin, tmp);
//		} while (tmp.find('/') != std::string::npos || tmp.find('\\') != std::string::npos ||
//			tmp.find(':') != std::string::npos || tmp.find('*') != std::string::npos ||
//			tmp.find('?') != std::string::npos || tmp.find('"') != std::string::npos ||
//			tmp.find('<') != std::string::npos || tmp.find('>') != std::string::npos ||
//			tmp.find('|') != std::string::npos);
//		if (std::experimental::filesystem::exists("./files directory/" + tmp)) {
//			if (!std::experimental::filesystem::is_directory("./files directory/" + tmp)) {
//				std::string decision;
//				do {
//					std::cout << std::endl << "Are you sure you want delete selected file? (Y/N)" << std::endl;
//					std::cin >> decision;
//				} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//
//				if (decision == "Y" || decision == "y") {
//					std::remove(("./files directory/" + tmp).c_str());
//				}
//				else {
//					std::cout << std::endl << "Operation canceled." << std::endl;
//				}
//			}
//			else {
//				std::cout << std::endl << "Selected object is directory" << std::endl;
//				std::string decision;
//				do {
//					std::cout << std::endl << "Do you want to delete directory and everything inside file? (Y/N)" << std::endl;
//					std::cin >> decision;
//				} while (decision != "Y" && decision != "y" && decision != "N" && decision != "n");
//
//				if (decision == "Y" || decision == "y") {
//					std::experimental::filesystem::remove_all(("./files directory/" + tmp).c_str());
//					std::experimental::filesystem::remove(("./files directory/" + tmp).c_str());
//				}
//				else {
//					std::cout << std::endl << "Operation canceled." << std::endl;
//				}
//			}
//		}
//		else {
//			std::cout << "No such file found!" << std::endl;
//		}
//	}
//	std::cin.ignore(INT_MAX, '\n');
//} while (!exitFlag);
//std::cout << std::endl << "Exiting..." << std::endl;