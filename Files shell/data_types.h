#pragma once
#ifndef DATA_TYPES
#define DATA_TYPES

namespace data_types {

	class CollegeData {
	public:
		enum fileType {
			StudentFileBin = 0,
			LecturerFileBin = 1,
			GroupFileBin = 2,
			StudentFile = 3,
			LecturerFile = 4,
			GroupFile = 5
		};
	};

	class StudentData : public CollegeData {
	public:
		char name[255];
		char surname[255];
		char patronymic[255];
		char groupCode[255];
		int absentCnt;
		float avgMark;
	};
	class LecturerData : public CollegeData {
	public:
		char name[255];
		char surname[255];
		char classTeachedOf[255];
		char lecturerIn[255];
		char lecturerSubjects[255];
		int salary;
	};
	class GroupData : public CollegeData {
	public:
		char groupName[255];
		char classTeacher[255];
		char groupFaculty[255];
		int studentsCourse;
		int studentsCount;
	};

}

#endif