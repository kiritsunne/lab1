#pragma once

#include<string>
#include"Circle.h"

using namespace std;
string SaveToFile();
void SaveResultToFile(Circle &A, Circle &B, double result);
void SaveInitialDataToFile(Circle &A, Circle &B);
Circle InputFromFile();
bool CheckExistFile(string &filePath);
bool CreateNewFile(string &filePath);
string EnterFilePath();