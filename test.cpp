#include "Circle.h"
#include <cmath>
#include <iostream>
#include "task.h"
#define NUMOFTEST 5
#define NUM 6

const double circleData[NUMOFTEST][NUM] = { {0.0, 0.0, 10.0, 0.0, 0.0, 1.0},
										{0.0, 0.0, 5.0, 10.0, 10.0, 0.0},
										{0.0, 0.0, 4.0, 6.0, 6.0, 2.0}, 
										{0.0, 0.0, 4.75, 0.0, 5.0, 1.0}, 
										{0.0, 0.0, 6.0, 0.0, 5.0, 6.0}};
double answer[NUMOFTEST] = { 3.14159265358, 0.0, 0.0, 1.014702998982239, 54.88172418871727 };
using namespace std;

void Test() {
	
	Circle A, B;
	for (int i = 0; i < NUMOFTEST; ++i) {
		A = Circle(circleData[i][0], circleData[i][1], circleData[i][2]);
		B = Circle(circleData[i][3], circleData[i][4], circleData[i][5]);
		if (fabs(Square(A, B) - answer[i]) > 0.0000001) {
			cout << "Тест  " << i + 1 << " не пройден " << endl << endl
				<< "Программа будет закрыта" << endl
				<< "Окружность А:\n    Центр (" << A.GetXCoord() << ", " << A.GetYCoord() << ") R = " << A.GetRadius() << endl
				<< "Окружность B:\n    Центр (" << B.GetXCoord() << ", " << B.GetYCoord() << ") R = " << B.GetRadius() << endl
				<< "Ожидаемый результат: " << answer[i] << endl
				<< "Полученный результат: " << Square(A, B) << endl;
			exit(0);
		}
	}
	cout << endl << "Тестирование успешно пройдено!" << endl;
}