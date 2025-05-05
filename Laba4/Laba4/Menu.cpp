#include "Menu.h"
#include "Applicants.h"
#include "Data.h"
#include "FileMenu.h"
#include "SortMenu.h"
#include <iostream>

using namespace std;

void PrintMenu() {
	cout << "\n----------------Главное меню----------------\n";
	cout << "\n1)Добавить абитуриентов";
	cout << "\n2)Печать абитуриентов";
	cout << "\n3)Вывод абитуриентов в виде таблицы";
	cout << "\n4)Очистить динамическую память";
	cout << "\n5)Работа с базами данных";
	cout << "\n6)Сортировка базы данных";
	cout << "\n0)Выйти";
}

void Exercise1(){
	CreateApplicant();
	TableAutoResize();
	cout << "\nАбитуриент добавлен в динамическую память\n";
}

void Exercise2() {
	DisplayApplicants();
}

void Exercise3(){
	DisplayTableApplicants();
}

void Exercise4() {
	applicants.Clear();
	cout << "\nДинамическая память очищена\n";
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
		int exercise = GetCheckIntData((char*)"\n\nВведите номер действия: ", (char*)"\nОшибка ввода, попробуйте снова");
		
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
			default: { cout << "\nДействия под таким номером нет, попробуйте снова."; break; }
		}

		system("pause");
		system("cls");
	}
}