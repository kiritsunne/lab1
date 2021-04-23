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
//Меню сохранения в файл
string SaveToFile() {
	cout << "Сохранение:" << endl
		<< "1 - Сохранить в существующий файл" << endl
		<< "2 - Сохранить в новый файл" << endl;
	int userChoice = -1;
	input(userChoice);
	string filePath;
	while (!(userChoice >= 1 && userChoice <= 2)) {
		cout << "Такого пункта меню не существует. Введите корректное значение" << endl;
		input(userChoice);
	}
	switch (userChoice)
	{
	//сохранение в существующий файл
	case INEXISTSAVE: {
		filePath = EnterFilePath();
		while (!CheckExistFile(filePath)) {
			cout << "Введите корректный путь к файлу" << endl;
			filePath = EnterFilePath();
		}
		break;
	}
	//сохранение в новый файл
	case INMEWSAVE: {
		filePath = EnterFilePath();
		while (!CreateNewFile(filePath)) {
			cout << "Введите корректный путь к файлу" << endl;
			filePath = EnterFilePath();
		}
		break;
	}
	}
	return filePath;
}
//Сохранение результата в файл
void SaveResultToFile(Circle &A, Circle &B, double result)
{
	ofstream file(SaveToFile(), ios_base::app);
	if (file.is_open()) {
		file << "Окружность А:\n    Центр (" << A.GetXCoord() << ", " << A.GetYCoord() << ") R = " << A.GetRadius() << endl
			<< "Окружность B:\n    Центр (" << B.GetXCoord() << ", " << B.GetYCoord() << ") R = " << B.GetRadius() << endl
			<< "Площадь пересечения окружностей: S = " << result << endl << endl << endl;
		cout << "Сохранение завершено" << endl;
	}
	else {
		cout << "Не удалось открыть файл" << endl;
	}
	
	file.close();
}
//Сохранение начальных данных в файл
//если формат сохранения начальных данных будет нарушен
//программа не распознает их при чтении начальных данных из файла
void SaveInitialDataToFile(Circle & A, Circle & B)
{
	ofstream file(SaveToFile(), ios_base::app);
	if (file.is_open()) {
		file << "[INPUT]" << endl
			<< "Окружность A:" << endl
			<< "координата X: " << A.GetXCoord() << endl
			<< "координата Y: " << A.GetYCoord() << endl
			<< "радиус: " << A.GetRadius() << endl
			<< "[INPUT]" << endl
			<< "Окружность B:" << endl
			<< "координата X: " << B.GetXCoord() << endl
			<< "координата Y: " << B.GetYCoord() << endl
			<< "радиус: " << B.GetRadius() << endl << endl;
		cout << "Сохранение завершено" << endl;
	}
	else {
		cout << "Не удалось открыть файл" << endl;
	}
	
	file.close();
}
//ввод из файла
Circle InputFromFile()
{
	string filePath;
	filePath = EnterFilePath();

	while (!CheckExistFile(filePath)) {
		cout << "Введите корректный путь к файлу" << endl;
		filePath = EnterFilePath();
	}

	ifstream file(filePath, ios_base::binary);
	double x = 0, y = 0, radius = 0;
	
	bool 
		//если пользователь соглавсен использовать
		//представлнные ему данные окружности
		//то флаг переходит в значение true
		agreeFlag = false, 
		
		//true - если в файле нет данных для выбора
		emptyDataFlag = true, 

		//true - если данные для ввода корректны
		//если есть ошибка в представлении данных в файле,
		//программа их пропускает и выводит
		//сообщение о неккоректности данных значений
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
			
			while (bufString != "радиус:") {
				file >> bufString;
			}
			correctFileInputFlag &= (fileInput(file, radius) && radius > 0.0);
			
			
			if (correctFileInputFlag) {
				cout << "Окружность:\n    Центр (" << x << ", " << y << ") R = " << radius << endl
					<< "Выбрать данную окружность?" << endl
					<< "1 - Да" << endl
					<< "0 - Нет" << endl;
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
		cout << "Нет данных для выбора" << endl;
	}
	file.close();
	return bufCircle;
} 
//Проверка существующего файла
bool CheckExistFile(string &filePath) {
	bool correctFileFlag = false;
	if (fs::exists(fs::status(filePath))) {
		correctFileFlag = true;
	}
	else {
		cout << "Файл не существует" << endl;
		correctFileFlag = false;
	}
	if (correctFileFlag && !fs::is_regular_file(fs::status(filePath))) {
		cout << "Не регулярный файл. Запись и чтение невозможны" << endl;
		correctFileFlag = false;
	}
	return correctFileFlag;
}
//создание файла для сохранение
bool CreateNewFile(string &filePath) {
	
	if (fs::exists(fs::status(filePath))) {
		cout << "Такой файл уже существует" << endl;
		return false;
	}

	bool correctFileFlag = false;
	ofstream file(filePath);

	if (file.is_open()) {
		if (!fs::is_regular_file(fs::status(filePath))) {
			cout << "Не регулярный файл. Запись и чтение невозможны" << endl;
			correctFileFlag = false;
		}
		else {
			cout << "Файл создан и готов к записи" << endl;
			correctFileFlag = true;
		}
	}

	else {
		cout << "Файл не создан" << endl;
		cout << "Неккоректно введен путь к файлу" << endl
			<< "Проверьте вводимый путь и расширение файла" << endl;
		correctFileFlag = false;
	}

	file.close();
	return correctFileFlag;
}
//ввод пути к файлу и его проверка
string EnterFilePath()
{
	string filePath = "";
	unsigned int sizeOfPath = UINT32_MAX;
	cout << "Введите путь к файлу. Расширение файла .txt" << endl;
	input(filePath);
	sizeOfPath = filePath.length();
	while (!(filePath.find(".txt") < sizeOfPath)) {
		cout << "Некорректно введен путь к файлу" << endl
			<< "Проверьте вводимый путь и расширение файла" << endl;
		input(filePath);
		sizeOfPath = filePath.length();
	}
	return filePath;
}