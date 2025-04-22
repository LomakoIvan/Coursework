#include "Data.h"
#include "Memory.h"
#include <iostream>

using namespace std;

Table table;

//Program wait user input and return input line
char* ReadLine() {
	char* ptr = nullptr;
	char simbol = ' ';
	int size = 1;
	int simbol_count = 0;

	while (simbol != '\0') {
		simbol = cin.get();
		simbol_count++;

		if (simbol_count >= size) {
			size *= 2;
			ResizeAllocatedMemory((void*&)ptr, sizeof(char) * size);
		}
		if (simbol == '\n') {
			size = simbol_count + 1;
			ResizeAllocatedMemory((void*&)ptr, sizeof(char) * size);
			simbol = '\0';
		}

		ptr[simbol_count - 1] = simbol;
	}

	return ptr;
}
	
//Use ReadLine() and check on russian and english simbols
char* GetCheckNameData(char* alarm = (char*)"", char* warning = (char*)"") {
	char* text = nullptr;

	while (true) {
		bool isFail = false;

		cout << alarm;
		text = ReadLine();

		int i = 0;
		while (text[i] != '\0') {
			bool condition_english = (text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z');
			bool condition_russian = (text[i] >= 'А' && text[i] <= 'Я') || (text[i] >= 'а' && text[i] <= 'я') || text[i] == 'Ё' || text[i] == 'ё';
			bool condition_space = (text[i] == ' ');

			if (!(condition_english || condition_russian || condition_space)) {
				isFail = true;
				break;
			}

			i++;
		}

		if (isFail) { cout << warning; }
		else { return text; }
	}
}

//Return address
char* GetCheckAddrData(char* alarm = (char*)"", char* warning = (char*)"")
{
	char* text = nullptr;
	while (true) {
		bool isFail = false;

		cout << alarm;
		text = ReadLine();

		int i = 0;
		while (text[i] != '\0') {
			bool condition_english = (text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z');
			bool condition_russian = (text[i] >= 'А' && text[i] <= 'Я') || (text[i] >= 'а' && text[i] <= 'я') || text[i] == 'Ё' || text[i] == 'ё';
			bool condition_space = (text[i] == ' ' || text[i] == '/' || text[i] == '№' || text[i] == ';' || text[i] == '-' || text[i] == '.' || text[i] == ',');
			bool condition_numbers = (text[i] >= '0' && text[i] <= '9');

			if (!(condition_english || condition_russian || condition_space || condition_numbers)) {
				isFail = true;
				break;
			}

			i++;
		}

		if (isFail) { cout << warning; }
		else { return text; }
	}
}

//Return date text in format 27.12.2006
char* GetCheckDateData(char* alarm = (char*)"", char* warning = (char*)"")
{
	char* text = nullptr;
	while (true) {
		bool isFail = false;

		cout << alarm;
		text = ReadLine();

		int i = 0;
		while (text[i] != '\0') {
			if (!((text[i] >= '0' && text[i] <= '9') || text[i] == '.')) {
				isFail = true;
				break;
			}
			i++;
		}

		if (isFail || strlen(text) != 10 || text[2] != '.' || text[5] != '.') { cout << warning; }
		else {
			char cday[3]{ text[0], text[1], '\0'};
			char cmonth[3]{ text[3], text[4], '\0'};
			char cyear[5]{ text[6], text[7], text[8], text[9], '\0'};

			int day = CharArrayToInt(cday, 2);
			int month = CharArrayToInt(cmonth, 2);
			int year = CharArrayToInt(cyear, 4);

			if (year >= 9999 || year <= 0) { cout << warning; continue; }
			if (month > 12 || month <= 0) { cout << warning; continue; }
			if (day > GetDaysInMonth(month, year) || day <= 0) { cout << warning; continue; }

			return text;
		}
	}
}

//Convert int to char array (char*)
char* IntToCharArray(int number) {
	char* data = nullptr;
	int length = 0;
	int temp = number;

	if (temp == 0) { length = 1; }
	while (temp != 0) {
		temp /= 10;
		length++;
	}

	data = (char*)AllocateMemory(sizeof(char) * (length + 1));

	for (int i = 0; i < length; i++) {
		int ten = 1;
		for (int j = 0; j < length - i - 1; j++) {
			ten *= 10;
		}
		data[i] = (char)(number / ten % 10 + 48);
	}
	data[length] = '\0';

	return data;
}

//Convert char* to int
int CharArrayToInt(char* text, int length) {
	if (text == nullptr) { return -1; }

	int data = 0;
	for (int i = 0; i < length; i++) {
		int ten = 1;

		for (int j = 0; j < length - i - 1; j++) {
			ten *= 10;
		}

		data += ((int)text[i] - 48) * ten;
	}

	return data;
}

//Return user input (int data)
int GetCheckIntData(char* alarm = (char*)"", char* warning = (char*)"") {
	char* text = nullptr;

	while (true) {
		bool isFail = false;

		cout << alarm;
		text = ReadLine();

		int length = 0;
		int i = 0;
		while (text[i] != '\0') {
			length++;
			if ((text[i] < '0' || text[i] > '9') && text[i] != '-') {
				isFail = true;
				break;
			}
			i++;
		}

		if (isFail || length == 0) { cout << warning; }
		else { return CharArrayToInt(text, length); }
	}
}

//Return number of days in a month
int GetDaysInMonth(int month, int year)
{
	return 28 + (int)(month + floor(month / 8)) % 2 + 2 % month +
		   floor((2 - ((year % 4) * ((year % 100) + (year % 400)) + 2) %
		   ((year % 4) * ((year % 100) + (year % 400)) + 1)) / month) +
		   floor(1 / month) - floor((1 - ((year % 4) * ((year % 100) +
		   (year % 400)) + 2) % ((year % 4) * ((year % 100) + (year % 400)) + 1)) / month);
}

//Table Init
void TableInit() {
	table.column_count = 5;
	table.column_size = (int*)AllocateMemory(sizeof(int) * table.column_count);
	for (int i = 0; i < table.column_count; i++) {
		table.column_size[i] = 16;
		table.size += table.column_size[i];
	}
}

//Print all applicants
void DisplayApplicants() {
	cout << "\n------------------Список всех абитуриентов------------------\n";
	applicants.DisplayFrontToBack();

	/*for (int i = 0; i < applicants_count; i++) {
		cout << "\nАбитуриент номер " << i + 1;
		cout << "\nФИО: " << applicants[i].name;
		cout << "\nАдрес: " << applicants[i].addr;
		cout << "\nКоличество баллов: " << applicants[i].mark << endl;
	}*/
}

//Write line in format +--------------+
void PrintBorderLine() {
	cout << "+";
	for (int i = 0; i < table.size - 1; i++) {
		cout << "-";
	}
	cout << "+\n";
}

//Write line in format +----+-----+---+
void PrintNextLine() {
	cout << "|" << endl << "+";

	int size1 = table.column_size[0] + table.column_size[1];
	int size2 = size1 + table.column_size[2];
	int size3 = size2 + table.column_size[3];

	for (int i = 0; i < table.size; i++) {
		if (i == table.column_size[0] || i == size1 || i == size2 || i == size3) {
			cout << "+";
		}
		else if (i != 1)
			cout << "-";
	}
	cout << "+\n";
}

//Write line in format |     text     |
void PrintTableLine(char* text, int str_len, bool next_line = true) {
	int length = strlen(text);
	cout << "|";

	for (int i = 0; i <= str_len - 1; i++) {
		if (i == (str_len - length) / 2) {
			cout << text;
			i += length;
		}
		else { cout << " "; }
	}

	if (next_line) {
		PrintNextLine();
	}
}

//Write line in format |     text     | \n +----+-----+---+
void PrintTableText(char* text, int str_len, bool next_line = true) {
	int length = strlen(text);

	cout << "|";
	for (int i = 0; i < str_len; i++) {
		if (i == (str_len - length) / 2) {
			cout << text;
			i += length;
		}
		else { cout << " "; }
	}

	if (next_line) { PrintNextLine(); }
}

//Rescale table columns on content
void TableAutoResize() {
	table.size = 0;
	int length = 0;
	
	int applicants_count = applicants.GetNodeCount();
	Deck temp_deck;
	temp_deck.Init();

	for (int i = 0; i < applicants_count; i++) {
		Applicant* person = applicants.pop_front();
		temp_deck.push_back(*person);

		length = strlen(person->name);
		if (length > table.column_size[1]) {
			table.column_size[1] += length - table.column_size[1] + 4;
		}

		length = strlen(person->addr);
		if (length > table.column_size[3]) {
			table.column_size[3] += length - table.column_size[3] + 4;
		}

		length = strlen(person->date);
		if (length > table.column_size[4]) {
			table.column_size[4] += length - table.column_size[4] + 4;
		}
	}

	for (int i = 0; i < table.column_count; i++) {
		table.size += table.column_size[i];
	}

	applicants = temp_deck;
}

//Write table in console
void DisplayTableApplicants() {
	cout << endl;

	PrintBorderLine();
	PrintTableLine((char*)"Таблица абитуриентов", table.size, true);
	PrintTableLine((char*)"Номер", table.column_size[0], false);
	PrintTableLine((char*)"ФИО", table.column_size[1], false);
	PrintTableLine((char*)"Баллы", table.column_size[2], false);
	PrintTableLine((char*)"Адрес", table.column_size[3], false);
	PrintTableLine((char*)"Дата", table.column_size[4], true);

	Deck temp_deck;
	temp_deck.Init();
	int node_count = applicants.GetNodeCount();

	for (int i = 0; i < node_count; i++) {
		Applicant* person = applicants.pop_front();
		temp_deck.push_back(*person);

		PrintTableText(IntToCharArray(i + 1), table.column_size[0], false);
		PrintTableText(person->name, table.column_size[1], false);
		PrintTableText(IntToCharArray(person->mark), table.column_size[2], false);
		PrintTableText(person->addr, table.column_size[3], false);
		PrintTableText(person->date, table.column_size[4], true);
	}

	applicants = temp_deck;

	cout << endl;
}

//Create new Applicant and return him
void CreateApplicant() {
	Applicant new_applicant;

	char* name = GetCheckNameData((char*)"Введите ФИО абитуриента: ", (char*)"Ошибка ввода\n");
	char* addr = GetCheckAddrData((char*)"Введите адрес абитуриента: ", (char*)"Ошибка ввода\n");
	int mark = GetCheckIntData((char*)"Введите баллы абитуриента: ", (char*)"Ошибка ввода\n");
	char* date = GetCheckDateData((char*)"Введите дату: ", (char*)"Ошибка ввода\n");

	char* new_name = (char*)AllocateMemory(sizeof(char) * strlen(name) + 1);
	char* new_addr = (char*)AllocateMemory(sizeof(char) * strlen(addr) + 1);
	char* new_date = (char*)AllocateMemory(sizeof(char) * strlen(date) + 1);

	strcpy_s(new_name, strlen(name) + 1, name);
	strcpy_s(new_addr, strlen(addr) + 1, addr);
	strcpy_s(new_date, strlen(date) + 1, date);

	new_applicant.name = new_name;
	new_applicant.addr = new_addr;
	new_applicant.date = new_date;
	new_applicant.mark = mark;

	applicants.push_back(new_applicant);
}