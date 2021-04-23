#pragma once

#include<iostream>
#include<fstream>
#include"Circle.h"

using namespace std;

template <typename NUM> void input(NUM& arg);
template <typename NUM> bool fileInput(ifstream &file, NUM &arg);

template <typename NUM> inline void input(NUM &arg)
{
	NUM _buffer; bool error;

	while (true) {
		cin >> _buffer;
		error = (cin.fail() || cin.bad());
		if (error) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "Ошибка ввода! Повторите, пожалуйста" << endl;
		}
		else break;
	}
	cin.ignore(cin.rdbuf()->in_avail());
	arg = _buffer;
}

template <typename NUM> inline bool fileInput(ifstream &file, NUM &arg)
{
	NUM _buffer; bool error;

		file >> _buffer;
		
		error = (file.bad() || file.fail());
		if (error) {
			cout << "Ошибка чтения окружности!" << endl;
			file.clear();
			file.ignore();
			return false;
		}
		else {
			arg = _buffer;
			return true;
		}
}