//
// File: main.cpp
// Project: Arbitrary Precision math library
// Created by Dalton Herrewynen on Feb. 6 2023
//

#include <iostream>
#include <string>
#include "ArbitraryPrecisionInt.h"

using namespace std;

int main(int argNum, char* args[]){
	string buffer;
	unsigned char bytes[16];
	APint bigint=APint();
	cout<<"Enter numbers (0-255): ";
	getline(cin, buffer, '\n');
	buffer+=" ";

	int j=0;//number of bytes found
	unsigned char userInput[16];
	string numberHolder;
	for(int i=0; i<16; ++i){
		bytes[i]=0;
		userInput[i]=0;
	}
	for(int i=0; i<buffer.length()&&j<16; ++i){//convert string numbers into array of numbers
		numberHolder+=buffer.at(i);
		if(buffer.at(i)==' '){
			if(!numberHolder.empty() && numberHolder!=" "){
				int number=stoi(numberHolder);
				userInput[j]=(unsigned char) (number%255);
				++j;
			}
			numberHolder="";
		}
	}

	return 0;
}
