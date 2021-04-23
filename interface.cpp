#include "interface.h"
#include<iostream>
#include<locale.h>
#include"task.h"
#include"enter.h"
#include "test.h"
#include"Circle.h"
#include"file.h"
using namespace std;
//именнованный массив для выбора пункта меню
enum menu {
	EXIT,
	TASK,
	TEST
};
//именнованный массив для выбора пункта подменю
enum taskmenu {
	RETURN,//назад
	KEYBORD,//ввод с клавиатуры
	INP_FILE//ввод из файла
};
//функция для вывода приветствия
void Greatings()
{
	cout << "=============" << endl
		<< "Вересова В.А." << endl
		<< "группа №404" << endl
		<< "Email: daiti.ru.ua@gmail.com" << endl
		<< "Лабораторная работа №1" << endl
		<< "Вариант №11" << endl
		<< "Для двух окружностей (в плоскости) определить," << endl
		<< "имеют ли они общую область, и найти площадь данной области." << endl
		<< "=============" << endl;
	system("pause");
}
//функция для вывода и взаимодействия с меню
void Menu()
{
	setlocale(LC_ALL, "RU");

	int userChoice = 0;

	do
	{
		system("cls");
		cout << "Лабораторная работа №1" << endl
			<< "1 - Расчет площади пересечения двух окружностей" << endl
			<< "2 - Тестирование" << endl
			<< "0 - Выход" << endl;

		input(userChoice);

		switch (userChoice)
		{
		case TASK: {
			system("cls");
			MenuTask();
			break;
		}
		case TEST: {
			system("cls");
			cout << "Тестирование" << endl << endl;
			Test();
			system("pause");
			break;
		}
		case EXIT: break;
		default: {
			cout << "Введите корректное значение!" << endl;
			system("pause");
			break;
		}
		}

	} while (userChoice != EXIT);
}
//функция для вывода и взимоействия с пунктами подменю
void MenuTask()
{
	setlocale(LC_ALL, "RU");

	int userChoice = 0;
	double x = 0, y = 0, radius = 0;

	//флаг выхода из подменю
	//false - не выходить из подменю
	//true - выход из подменю
	bool flagExitSubMenu = true;

	//флаг сохранения в файл
	//false - не сохранять данные в файл
	//true - сохранять данные в файл
	bool flagSaveToFile = false;

	Circle circle[2];

	do
	{
		system("cls");
		cout << "1 - Ввод с клавиатуры" << endl
			<< "2 - Ввод из файла" << endl
			<< "0 - Назад" << endl;
		input(userChoice);

		switch (userChoice)
		{
		//ввод данных с клавиатуры
		case KEYBORD: {
			for (int i = 0; i < 2; ++i) {
				cout << "Введите координаты центра окружности №" << i + 1 << " (x, y):" << endl;
				input(x);
				input(y);
				cout << "Введите радиус окружности №" << i + 1 << ":" << endl;
				input(radius);
				while (!(radius > 0)) {
					cout << "Радиус не может быть отрицательным или нулевым." << endl
						<< "Введите корректное значение" << endl;
					input(radius);
				}
				circle[i] = Circle(x, y, radius);
			}
			break;
		}
		//ввод из файла
		case INP_FILE: {
			while (circle[0].GetRadius() == 0) {
				cout << "Данные для окружности А" << endl;
				circle[0] = InputFromFile();
			}
			while (circle[1].GetRadius() == 0) {
				cout << "Данные для окружности В" << endl;
				circle[1] = InputFromFile();
			}
			break;
		}
		//вернуться в главное меню
		case RETURN: {
			flagExitSubMenu = false;
			break;
		}
		default: {
			cout << "Введите корректное значение!" << endl;
			system("pause");
			break;
		}
		}
		//выполняется если были введены данные двух окружностей
		//и не выбран пункт НАЗАД
		if (flagExitSubMenu && circle[0].GetRadius() > 0 && circle[1].GetRadius() > 0) {
			cout << "Окружность А:\n    Центр (" << circle[0].GetXCoord() << ", " << circle[0].GetYCoord() << ") R = " << circle[0].GetRadius() << endl
				<< "Окружность B:\n    Центр (" << circle[1].GetXCoord() << ", " << circle[1].GetYCoord() << ") R = " << circle[1].GetRadius() << endl
				<< "Площадь пересечения окружностей: S = " << Square(circle[0], circle[1]) << endl << endl;

			cout << "Желаете сохранить исходные данные в файл?" << endl
				<< "1 - Да" << endl
				<< "0 - Нет" << endl;
			input(flagSaveToFile);
			if (flagSaveToFile)
				SaveInitialDataToFile(circle[0], circle[1]);

			cout << "Желаете сохранить результат в файл?" << endl
				<< "1 - Да" << endl
				<< "0 - Нет" << endl;
			input(flagSaveToFile);
			if (flagSaveToFile)
				SaveResultToFile(circle[0], circle[1], Square(circle[0], circle[1]));
			
			userChoice = RETURN;
		}
		system("pause");

	} while (userChoice != RETURN);
}