#include "Menu.h"
#include "Applicants.h"
#include "Data.h"
#include "FileMenu.h"
#include "SortMenu.h"
#include <iostream>

using namespace std;

void PrintMenu() {
	cout << "\n----------------������� ����----------------\n";
	cout << "\n1)�������� ������������";
	cout << "\n2)������ ������������";
	cout << "\n3)����� ������������ � ���� �������";
	cout << "\n4)�������� ������������ ������";
	cout << "\n5)������ � ������ ������";
	cout << "\n6)���������� ���� ������";
	cout << "\n0)�����";
}

void Exercise1(){
	CreateApplicant();
	TableAutoResize();
	cout << "\n���������� �������� � ������������ ������\n";
}

void Exercise2() {
	DisplayApplicants();
}

void Exercise3(){
	DisplayTableApplicants();
}

void Exercise4() {
	applicants.Clear();
	cout << "\n������������ ������ �������\n";
}

void Exercise5() {
	system("cls");
	FileMenu();
}

void Exercise6() {
	system("cls");
	SortMenu();
}

void Menu() {
	applicants.Init();
	TableInit();
	TableAutoResize();

	bool close = false;
	
	while (!close) {
		PrintMenu();
		int exercise = GetCheckIntData((char*)"\n\n������� ����� ��������: ", (char*)"\n������ �����, ���������� �����");
		
		switch (exercise) {
			case 1: { Exercise1(); break; }
			case 2: { Exercise2(); break; }
			case 3: { Exercise3(); break; }
			case 4: { Exercise4(); break; }
			case 5: { Exercise5(); break; }
			case 6: { Exercise6(); break; }
			case 0: {
				close = true;
				applicants.Clear();
				return;
			}
			default: { cout << "\n�������� ��� ����� ������� ���, ���������� �����."; break; }
		}

		system("pause");
		system("cls");
	}
}