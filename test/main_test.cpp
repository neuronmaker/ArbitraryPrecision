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
	if(argNum<=1){//print error message if there are no arguments on the command line
		cout<<"You need to supply at least 1 argument"<<endl;
		cout<<"Arguments are the names of the tests you wish to run"<<endl;
		return 0;
	}
	string argument;
	int retVal=0;
	for(int i=1; i<argNum && retVal==0; ++i){
		invalidTest(argument);
	}
	return 0;
}