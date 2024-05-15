//
// File: main_test.cpp
// Project: Arbitrary Precision math library
// Created by Dalton Herrewynen on May 15, 2024
//
#include "test_utils.h"
#include <string>
#include <iostream>

using namespace std;

void invalidTest(string testName){
	cout<<"Invalid test name: "<<testName<<endl;
}

int main(int argNum, char* args[]){
	if(argNum<=2){//print error message if there are less than 2 additional arguments to the command line
		cout << "You need to supply at least 2 arguments" << endl;
		cout << "Argument 1: \"-s\" silences printed output, anything else allows printed output" << endl;
		cout << "Next arguments are the values of each test to run." << endl;
		return 0;
	}
	string argument=args[1];
	bool print=(argument!="-s");//if first argument is -s, silence printed outputs
	for(int i=0; i<argNum; ++i){
		invalidTest(argument);
	}
	return 0;
}