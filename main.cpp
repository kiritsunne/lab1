#include<iostream>
#include<locale.h>
#include"interface.h"


using namespace std;

int main(void) {
	setlocale(LC_ALL, "RU");
	
	Greatings();
	Menu();

	return 0;
}