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
	system("cls");

	cout << "Варианты сортировки:";
	cout << "\n1) От меньшего к большему";
	cout << "\n2) От большего к меньшему";
	cout << "\n0) Вернуться в главное меню";

	while (true) {
		int option = GetCheckIntData((char*)"\n\nВыберете один из вариантов: ", (char*)"\nОшибка ввода.\n");

		switch (option) {
			case 1: {
				InsertSortMark(applicants, false);
				cout << "\nБаза данных была отсортированна по возрастанию\n";
				return;
			}
			case 2: {
				InsertSortMark(applicants, true);
				cout << "\nБаза данных была отсортированна по убыванию\n";
				return;
			}
			case 0: {
				return;
			}
			default: {
				cout << "\nВарианта под таким номером нет. Попробуйте снова.\n";
				break;
			}
		}
	}
}

void Exercise7() {
	system("cls");

	cout << "Варианты сортировки:";
	cout << "\n1) В алфавитном порядке";
	cout << "\n2) В обратном алфавитном порядке";
	cout << "\n0) Вернуться в главное меню";

	while (true) {
		int option = GetCheckIntData((char*)"\n\nВыберете один из вариантов: ", (char*)"\nОшибка ввода.\n");

		switch (option) {
		case 1: {
			InsertSortName(applicants, false);
			cout << "\nБаза данных была отсортированна в алфавитном порядке\n";
			return;
		}
		case 2: {
			InsertSortName(applicants, true);
			cout << "\nБаза данных была отсортированна в обратном алфавитном порядке";
			return;
		}
		case 0: {
			return;
		}
		default: {
			cout << "\nВарианта под таким номером нет. Попробуйте снова.\n";
			break;
		}
		}
	}
}

void Exercise8() {
	system("cls");

	cout << "Варианты сортировки:";
	cout << "\n1) От меньшего к большему";
	cout << "\n2) От большего к меньшему";
	cout << "\n0) Вернуться в главное меню";

	while (true) {
		int option = GetCheckIntData((char*)"\n\nВыберете один из вариантов: ", (char*)"\nОшибка ввода.\n");

		switch (option) {
		case 1: {
			HeapSortQueueMark(applicants, false);
			cout << "\nБаза данных была отсортированна по возрастанию\n";
			return;
		}
		case 2: {
			HeapSortQueueMark(applicants, true);
			cout << "\nБаза данных была отсортированна по убыванию\n";
			return;
		}
		case 0: {
			return;
		}
		default: {
			cout << "\nВарианта под таким номером нет. Попробуйте снова.\n";
			break;
		}
		}
	}
}

void Exercise9() {
	system("cls");

	cout << "Варианты сортировки:";
	cout << "\n1) В алфавитном порядке";
	cout << "\n2) В обратном алфавитном порядке";
	cout << "\n0) Вернуться в главное меню";

	while (true) {
		int option = GetCheckIntData((char*)"\n\nВыберете один из вариантов: ", (char*)"\nОшибка ввода.\n");

		switch (option) {
		case 1: {
			HeapSortQueueName(applicants, false);
			cout << "\nБаза данных была отсортированна в алфавитном порядке\n";
			return;
		}
		case 2: {
			HeapSortQueueName(applicants, true);
			cout << "\nБаза данных была отсортированна в обратном алфавитном порядке";
			return;
		}
		case 0: {
			return;
		}
		default: {
			cout << "\nВарианта под таким номером нет. Попробуйте снова.\n";
			break;
		}
		}
	}
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
				return;
			}
			default: { cout << "\nДействия под таким номером нет, попробуйте снова."; break; }
		}

		system("pause");
		system("cls");
	}
}