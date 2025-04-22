#include "FileMenu.h"
#include "Data.h"
#include "DataBase.h"
#include <iostream>

using namespace std;

void PrintFileMenu() {
	cout << "\n----------------���� ��� ������ � �������----------------\n";
	cout << "\n1)������� ���� ���� ������";
	cout << "\n2)��������� ���� ������";
	cout << "\n3)��������� ���� ������";
	cout << "\n4)������� ���� ������";
	cout << "\n0)��������� � ������� ����";
}

void FileMenuExercise1() {
	cout << "\n������� �������� ���� ������ (� �������� .bin): ";
	char* file_name = ReadLine();

	ofstream file = new_DB(file_name);
	if (!file.is_open()) {
		cout << "\n������, ���� ������ ������ ����� ������ .bin\n";
		return;
	}

	cout << "\n���� ������ � ��������� " << file_name << " ���� �������\n";
	file.close();
}

void FileMenuExercise2() {
	cout << "\n������� �������� ���� ������ (� ����������� .bin): ";
	char* file_name = ReadLine();

	if (save_DB(file_name)) {
		cout << "\n���� ������ ���� ��������� � ����\n";
	}
	else { cout << "\n������ ���������� ���� ������\n"; }
}

void FileMenuExercise3() {
	cout << "\n������� �������� ���� ������ (� ����������� .bin): ";
	char* file_name = ReadLine();

	if (load_DB(file_name)) {
		cout << "\n���� ������ ���� ��������� �� �����\n";
	}
	else { cout << "\n������ �������� ���� ������\n"; }

	TableAutoResize();
}

void FileMenuExercise5() {
	cout << "\n������� ��� ����� (� ����������� .bin): ";
	char* file_name = ReadLine();

	if (remove_DB(file_name)) {
		cout << "\n���� ���� ������ " << file_name << " ��� ������� ������\n";
	}
	else {
		cout << "\n���� �� ��� ������ ��� �� ���� ������������ ����������\n";
	}
}

void FileMenu() {
	while (true) {
		PrintFileMenu();

		int exercise = GetCheckIntData((char*)"\n\n������� ����� ��������: ", (char*)"\n������ �����. ���������� �����.");

		switch (exercise) {
		case 1: { FileMenuExercise1(); break; }
		case 2: { FileMenuExercise2(); break; }
		case 3: { FileMenuExercise3(); break; }
		case 4: { FileMenuExercise5(); break; }
		case 0: { return; break; }
		default: {
			cout << "\n�������� ��� ����� ������� ���. ���������� �����.\n";
			break;
		}
		}

		system("pause");
		system("cls");
	}
}