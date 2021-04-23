#include "interface.h"
#include<iostream>
#include<locale.h>
#include"task.h"
#include"enter.h"
#include "test.h"
#include"Circle.h"
#include"file.h"
using namespace std;
//������������ ������ ��� ������ ������ ����
enum menu {
	EXIT,
	TASK,
	TEST
};
//������������ ������ ��� ������ ������ �������
enum taskmenu {
	RETURN,//�����
	KEYBORD,//���� � ����������
	INP_FILE//���� �� �����
};
//������� ��� ������ �����������
void Greatings()
{
	cout << "=============" << endl
		<< "�������� �.�." << endl
		<< "������ �404" << endl
		<< "Email: daiti.ru.ua@gmail.com" << endl
		<< "������������ ������ �1" << endl
		<< "������� �11" << endl
		<< "��� ���� ����������� (� ���������) ����������," << endl
		<< "����� �� ��� ����� �������, � ����� ������� ������ �������." << endl
		<< "=============" << endl;
	system("pause");
}
//������� ��� ������ � �������������� � ����
void Menu()
{
	setlocale(LC_ALL, "RU");

	int userChoice = 0;

	do
	{
		system("cls");
		cout << "������������ ������ �1" << endl
			<< "1 - ������ ������� ����������� ���� �����������" << endl
			<< "2 - ������������" << endl
			<< "0 - �����" << endl;

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
			cout << "������������" << endl << endl;
			Test();
			system("pause");
			break;
		}
		case EXIT: break;
		default: {
			cout << "������� ���������� ��������!" << endl;
			system("pause");
			break;
		}
		}

	} while (userChoice != EXIT);
}
//������� ��� ������ � ������������ � �������� �������
void MenuTask()
{
	setlocale(LC_ALL, "RU");

	int userChoice = 0;
	double x = 0, y = 0, radius = 0;

	//���� ������ �� �������
	//false - �� �������� �� �������
	//true - ����� �� �������
	bool flagExitSubMenu = true;

	//���� ���������� � ����
	//false - �� ��������� ������ � ����
	//true - ��������� ������ � ����
	bool flagSaveToFile = false;

	Circle circle[2];

	do
	{
		system("cls");
		cout << "1 - ���� � ����������" << endl
			<< "2 - ���� �� �����" << endl
			<< "0 - �����" << endl;
		input(userChoice);

		switch (userChoice)
		{
		//���� ������ � ����������
		case KEYBORD: {
			for (int i = 0; i < 2; ++i) {
				cout << "������� ���������� ������ ���������� �" << i + 1 << " (x, y):" << endl;
				input(x);
				input(y);
				cout << "������� ������ ���������� �" << i + 1 << ":" << endl;
				input(radius);
				while (!(radius > 0)) {
					cout << "������ �� ����� ���� ������������� ��� �������." << endl
						<< "������� ���������� ��������" << endl;
					input(radius);
				}
				circle[i] = Circle(x, y, radius);
			}
			break;
		}
		//���� �� �����
		case INP_FILE: {
			while (circle[0].GetRadius() == 0) {
				cout << "������ ��� ���������� �" << endl;
				circle[0] = InputFromFile();
			}
			while (circle[1].GetRadius() == 0) {
				cout << "������ ��� ���������� �" << endl;
				circle[1] = InputFromFile();
			}
			break;
		}
		//��������� � ������� ����
		case RETURN: {
			flagExitSubMenu = false;
			break;
		}
		default: {
			cout << "������� ���������� ��������!" << endl;
			system("pause");
			break;
		}
		}
		//����������� ���� ���� ������� ������ ���� �����������
		//� �� ������ ����� �����
		if (flagExitSubMenu && circle[0].GetRadius() > 0 && circle[1].GetRadius() > 0) {
			cout << "���������� �:\n    ����� (" << circle[0].GetXCoord() << ", " << circle[0].GetYCoord() << ") R = " << circle[0].GetRadius() << endl
				<< "���������� B:\n    ����� (" << circle[1].GetXCoord() << ", " << circle[1].GetYCoord() << ") R = " << circle[1].GetRadius() << endl
				<< "������� ����������� �����������: S = " << Square(circle[0], circle[1]) << endl << endl;

			cout << "������� ��������� �������� ������ � ����?" << endl
				<< "1 - ��" << endl
				<< "0 - ���" << endl;
			input(flagSaveToFile);
			if (flagSaveToFile)
				SaveInitialDataToFile(circle[0], circle[1]);

			cout << "������� ��������� ��������� � ����?" << endl
				<< "1 - ��" << endl
				<< "0 - ���" << endl;
			input(flagSaveToFile);
			if (flagSaveToFile)
				SaveResultToFile(circle[0], circle[1], Square(circle[0], circle[1]));
			
			userChoice = RETURN;
		}
		system("pause");

	} while (userChoice != RETURN);
}