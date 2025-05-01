#include "DataBase.h"
#include "Memory.h"
#include "Applicants.h"
#include <iostream>

using namespace std;

//Check file type on .bin
bool isBinFormat(char* file_name) {
	char* checker = strstr(file_name, ".bin");
	if (checker == nullptr || *(checker + 4) != '\0') {
		return false;
	}

	int i = 0;
	int point_count = 0;
	while (file_name[i] != '\0') {
		if (file_name[i] == '.') { point_count++; }
		if (point_count > 1) { break; }
		i++;
	}

	if (point_count > 1 || point_count == 0) {
		return false;
	}

	return true;
}

//Check file present
bool isFilePresent(char* file_name) {
	ifstream file(file_name, ios::binary);
	if (file.is_open()) {
		file.close();
		return true;
	}
	else { return false; }
}

//Create data base file and return ofstream
ofstream new_DB(char* file_name) {
	ofstream file;

	if (!isBinFormat(file_name)) {
		return file;
	}

	file.open(file_name, ios::binary | ios::trunc);

	if (!file) {
		cout << "\nОшибка создания файла базы данных\n";
		return file;
	}

	return file;
}

//If file present remove data base else write error
bool remove_DB(char* file_name) {
	//Check on file present and file format
	if (!isBinFormat(file_name)) { return false; }

	//Try to delete file
	bool isDelete = remove(file_name);

	if (isDelete == 0) {
		return true;
	}
	return false;
}

//Save data base in binary file
bool save_DB(char* file_name) {
	if (!isFilePresent(file_name)) {
		cout << "\nБазы данных с таким названием не существует\n";
		return false;
	}

	ofstream file(file_name, ios::binary | ios::trunc);
	if (!file.is_open()) { return false; }

	int count = applicants.GetNodeCount();
	Queue temp_queue;

	file.write((char*)&count, sizeof(int));
	for (int i = 0; i < count; i++) {
		Applicant person = *applicants.pop_front();
		temp_queue.push_front(person);

		file.write(person.name, sizeof(char) * 34);
		file.write((char*)&person.mark, sizeof(int));
		file.write(person.addr, sizeof(char) * 34);
		file.write(person.date, sizeof(char) * 12);
	}

	applicants = temp_queue;

	file.close();
	return true;
}

//Load data base with binary file to program memory
bool load_DB(char* file_name) {
	ifstream file(file_name, ios::binary);

	if (!file.is_open()) {
		return false;
	}

	int count = 0;
	file.read((char*)&count, sizeof(int));

	int applicants_count = applicants.GetNodeCount();

	for (int i = applicants_count; i < applicants_count + count; i++) {
		Applicant person;

		person.name = (char*)AllocateMemory(sizeof(char) * 34);
		person.addr = (char*)AllocateMemory(sizeof(char) * 34);
		person.date = (char*)AllocateMemory(sizeof(char) * 12);

		file.read(person.name, sizeof(char) * 34);
		file.read((char*)&person.mark, sizeof(int));
		file.read(person.addr, sizeof(char) * 34);
		file.read(person.date, sizeof(char) * 12);

		applicants.push_front(person);
	}

	file.close();
	return true;
}