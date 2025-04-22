#include "FileMenu.h"
#include "Data.h"
#include "DataBase.h"
#include <iostream>

using namespace std;

void PrintFileMenu() {
	cout << "\n----------------Меню для работы с файлами----------------\n";
	cout << "\n1)Создать файл базы данных";
	cout << "\n2)Сохранить базу данных";
	cout << "\n3)Загрузить базу данных";
	cout << "\n4)Удалить базу данных";
	cout << "\n0)Вернуться в главное меню";
}

void FileMenuExercise1() {
	cout << "\nВведите название базы данных (с форматом .bin): ";
	char* file_name = ReadLine();

	ofstream file = new_DB(file_name);
	if (!file.is_open()) {
		cout << "\nОшибка, база данных должна иметь формат .bin\n";
		return;
	}

	cout << "\nБаза данных с названием " << file_name << " была создана\n";
	file.close();
}

void FileMenuExercise2() {
	cout << "\nВведите название базы данных (с расширением .bin): ";
	char* file_name = ReadLine();

	if (save_DB(file_name)) {
		cout << "\nБаза данных была сохранена в файл\n";
	}
	else { cout << "\nОшибка сохранения базы данных\n"; }
}

void FileMenuExercise3() {
	cout << "\nВведите название базы данных (с расширением .bin): ";
	char* file_name = ReadLine();

	if (load_DB(file_name)) {
		cout << "\nБаза данных была загружена из файла\n";
	}
	else { cout << "\nОшибка загрузки базы данных\n"; }

	TableAutoResize();
}

void FileMenuExercise5() {
	cout << "\nВведите имя файла (с расширением .bin): ";
	char* file_name = ReadLine();

	if (remove_DB(file_name)) {
		cout << "\nФайл базы данных " << file_name << " был успешно удален\n";
	}
	else {
		cout << "\nФайл не был найден или он имел неправильное расширение\n";
	}
}

void FileMenu() {
	while (true) {
		PrintFileMenu();

		int exercise = GetCheckIntData((char*)"\n\nВведите номер действия: ", (char*)"\nОшибка ввода. Попробуйте снова.");

		switch (exercise) {
		case 1: { FileMenuExercise1(); break; }
		case 2: { FileMenuExercise2(); break; }
		case 3: { FileMenuExercise3(); break; }
		case 4: { FileMenuExercise5(); break; }
		case 0: { return; break; }
		default: {
			cout << "\nДействия под таким номером нет. Попробуйте снова.\n";
			break;
		}
		}

		system("pause");
		system("cls");
	}
}