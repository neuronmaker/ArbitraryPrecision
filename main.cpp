//
// File: main.cpp
// Project: Arbitrary Precision math library
// Created by Dalton Herrewynen on Feb. 6 2023
//

#include <iostream>
#include "ArbitraryPrecisionInt.h"
#include <string>

using namespace std;

int main(){
	string buffer;
	unsigned char bytes[16];
	APint bigint;
	cout<<"Enter numbers (0-255): ";
	getline(cin, buffer, '\n');
	cout<<buffer<<endl;
	return 0;
}
