#include "file.h"
#include<filesystem>
#include<fstream>
#include<iostream>
#include<string>
#include"enter.h"

enum saveMenu {
	INEXISTSAVE = 1,
	INMEWSAVE
};

using namespace std;
namespace fs = std::experimental::filesystem;
//���� ���������� � ����
string SaveToFile() {
	cout << "����������:" << endl
		<< "1 - ��������� � ������������ ����" << endl
		<< "2 - ��������� � ����� ����" << endl;
	int userChoice = -1;
	input(userChoice);
	string filePath;
	while (!(userChoice >= 1 && userChoice <= 2)) {
		cout << "������ ������ ���� �� ����������. ������� ���������� ��������" << endl;
		input(userChoice);
	}
	switch (userChoice)
	{
	//���������� � ������������ ����
	case INEXISTSAVE: {
		filePath = EnterFilePath();
		while (!CheckExistFile(filePath)) {
			cout << "������� ���������� ���� � �����" << endl;
			filePath = EnterFilePath();
		}
		break;
	}
	//���������� � ����� ����
	case INMEWSAVE: {
		filePath = EnterFilePath();
		while (!CreateNewFile(filePath)) {
			cout << "������� ���������� ���� � �����" << endl;
			filePath = EnterFilePath();
		}
		break;
	}
	}
	return filePath;
}
//���������� ���������� � ����
void SaveResultToFile(Circle &A, Circle &B, double result)
{
	ofstream file(SaveToFile(), ios_base::app);
	if (file.is_open()) {
		file << "���������� �:\n    ����� (" << A.GetXCoord() << ", " << A.GetYCoord() << ") R = " << A.GetRadius() << endl
			<< "���������� B:\n    ����� (" << B.GetXCoord() << ", " << B.GetYCoord() << ") R = " << B.GetRadius() << endl
			<< "������� ����������� �����������: S = " << result << endl << endl << endl;
		cout << "���������� ���������" << endl;
	}
	else {
		cout << "�� ������� ������� ����" << endl;
	}
	
	file.close();
}
//���������� ��������� ������ � ����
//���� ������ ���������� ��������� ������ ����� �������
//��������� �� ���������� �� ��� ������ ��������� ������ �� �����
void SaveInitialDataToFile(Circle & A, Circle & B)
{
	ofstream file(SaveToFile(), ios_base::app);
	if (file.is_open()) {
		file << "[INPUT]" << endl
			<< "���������� A:" << endl
			<< "���������� X: " << A.GetXCoord() << endl
			<< "���������� Y: " << A.GetYCoord() << endl
			<< "������: " << A.GetRadius() << endl
			<< "[INPUT]" << endl
			<< "���������� B:" << endl
			<< "���������� X: " << B.GetXCoord() << endl
			<< "���������� Y: " << B.GetYCoord() << endl
			<< "������: " << B.GetRadius() << endl << endl;
		cout << "���������� ���������" << endl;
	}
	else {
		cout << "�� ������� ������� ����" << endl;
	}
	
	file.close();
}
//���� �� �����
Circle InputFromFile()
{
	string filePath;
	filePath = EnterFilePath();

	while (!CheckExistFile(filePath)) {
		cout << "������� ���������� ���� � �����" << endl;
		filePath = EnterFilePath();
	}

	ifstream file(filePath, ios_base::binary);
	double x = 0, y = 0, radius = 0;
	
	bool 
		//���� ������������ ��������� ������������
		//������������� ��� ������ ����������
		//�� ���� ��������� � �������� true
		agreeFlag = false, 
		
		//true - ���� � ����� ��� ������ ��� ������
		emptyDataFlag = true, 

		//true - ���� ������ ��� ����� ���������
		//���� ���� ������ � ������������� ������ � �����,
		//��������� �� ���������� � �������
		//��������� � �������������� ������ ��������
		correctFileInputFlag = true;

	string bufString;
	Circle bufCircle;

	while (!file.eof() && !agreeFlag) {
		file >> bufString;
		if (bufString == "[INPUT]") {
			emptyDataFlag = false;

			cout << "input" << endl;
			while (bufString != "X:") {
				file >> bufString;
			}
			correctFileInputFlag = fileInput(file, x);
			
			while (bufString != "Y:") {
				file >> bufString;
			}
			correctFileInputFlag &= fileInput(file, y);
			
			while (bufString != "������:") {
				file >> bufString;
			}
			correctFileInputFlag &= (fileInput(file, radius) && radius > 0.0);
			
			
			if (correctFileInputFlag) {
				cout << "����������:\n    ����� (" << x << ", " << y << ") R = " << radius << endl
					<< "������� ������ ����������?" << endl
					<< "1 - ��" << endl
					<< "0 - ���" << endl;
				input(agreeFlag);
				if (agreeFlag) {
					bufCircle = Circle(x, y, radius);
					agreeFlag = true;
				}	
			}
			else {
				agreeFlag = false;
			} 
			correctFileInputFlag = true;
		}		
	}
	if (emptyDataFlag == true) {
		cout << "��� ������ ��� ������" << endl;
	}
	file.close();
	return bufCircle;
} 
//�������� ������������� �����
bool CheckExistFile(string &filePath) {
	bool correctFileFlag = false;
	if (fs::exists(fs::status(filePath))) {
		correctFileFlag = true;
	}
	else {
		cout << "���� �� ����������" << endl;
		correctFileFlag = false;
	}
	if (correctFileFlag && !fs::is_regular_file(fs::status(filePath))) {
		cout << "�� ���������� ����. ������ � ������ ����������" << endl;
		correctFileFlag = false;
	}
	return correctFileFlag;
}
//�������� ����� ��� ����������
bool CreateNewFile(string &filePath) {
	
	if (fs::exists(fs::status(filePath))) {
		cout << "����� ���� ��� ����������" << endl;
		return false;
	}

	bool correctFileFlag = false;
	ofstream file(filePath);

	if (file.is_open()) {
		if (!fs::is_regular_file(fs::status(filePath))) {
			cout << "�� ���������� ����. ������ � ������ ����������" << endl;
			correctFileFlag = false;
		}
		else {
			cout << "���� ������ � ����� � ������" << endl;
			correctFileFlag = true;
		}
	}

	else {
		cout << "���� �� ������" << endl;
		cout << "����������� ������ ���� � �����" << endl
			<< "��������� �������� ���� � ���������� �����" << endl;
		correctFileFlag = false;
	}

	file.close();
	return correctFileFlag;
}
//���� ���� � ����� � ��� ��������
string EnterFilePath()
{
	string filePath = "";
	unsigned int sizeOfPath = UINT32_MAX;
	cout << "������� ���� � �����. ���������� ����� .txt" << endl;
	input(filePath);
	sizeOfPath = filePath.length();
	while (!(filePath.find(".txt") < sizeOfPath)) {
		cout << "����������� ������ ���� � �����" << endl
			<< "��������� �������� ���� � ���������� �����" << endl;
		input(filePath);
		sizeOfPath = filePath.length();
	}
	return filePath;
}