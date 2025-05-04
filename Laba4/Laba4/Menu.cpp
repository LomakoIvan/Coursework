#include "Menu.h"
#include "Applicants.h"
#include "Data.h"
#include "FileMenu.h"
#include "SortModule.h"
#include <iostream>

using namespace std;

void PrintMenu() {
	cout << "\n----------------Главное меню----------------\n";
	cout << "\n1)Добавить абитуриентов";
	cout << "\n2)Печать абитуриентов";
	cout << "\n3)Вывод абитуриентов в виде таблицы";
	cout << "\n4)Очистить динамическую память";
	cout << "\n5)Работа с базами данных";
	cout << "\n6)Сортировать вставками по полю \"Оценка\"";
	cout << "\n7)Сортировка вставками по полю \"ФИО\"";
	cout << "\n8)Сортировать Heap Sort по полю \"Оценка\"";
	cout << "\n9)Сортировка Heap Sort по полю \"ФИО\"";
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
	InsertSortMark(applicants);
}

void Exercise7() {
	InsertSortName(applicants);
}

void Exercise8() {
	heapSortQueueMark(applicants);
}

void Exercise9() {
	heapSortQueueName(applicants);
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
		case 7: { Exercise7(); break; }
		case 8: { Exercise8(); break; }
		case 9: { Exercise9(); break; }
		case 0: {
			close = true;
			applicants.Clear();
			break;
		}
		default: { cout << "\nДействия под таким номером нет, попробуйте снова."; break; }
		}

		system("pause");
		system("cls");
	}
}