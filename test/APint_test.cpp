//
// File: ArbitraryPrecisionInt_test.cpp
// Project: Arbitrary Precision math library
// Created by Dalton Herrewynen on May 15, 2024
//
#include "test_utils.h"
#include "APint.h"
#include <string>
#include <iostream>

using namespace std;
//declarations
int test_addition(bool);
int test_dumpBinString(); int test_byteReadWrite();
int test_printNumber(); int test_parseString();

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
	for(int i=1; i<argNum && retVal==0; ++i){//loop over all arguments unless one or more tests fail
		argument=args[i];
		if(argument=="dumpBinString") retVal=test_dumpBinString();//select the correct test to run by name
		else if(argument=="byteReadWrite") retVal=test_byteReadWrite();
		else if(argument=="printNumber") retVal=test_printNumber();
		else if(argument=="parseNumber") retVal=test_parseString();
		else invalidTest(argument);
	}
	return retVal;
}

/**
 * Tests printing the integer as a human-readable number
 * @return 0 upon success, anything else is a failure
 */
int test_printNumber(){
	cout<<"Testing the ability of the APInt to print a human-readable number"<<endl;
	APint bigint=APint(16);//2 bytes
	return 0;
}
/**
 * Tests parsing a number from a string
 * @return 0 upon success, anything else is a failure
 */
int test_parseString(){
	cout<<"Testing the ability of the APInt to read a number from a string"<<endl;
	APint bigint=APint(16);//2 bytes
	return 0;
}
/**
 * Test the ability to print the binary data from the integer structure as a string
 * @return 0 upon success, anything else is a failure
 */
int test_dumpBinString(){
	cout<<"Testing the APInt dumpBinString() function"<<endl;//print test name if not silenced
	APint bigint=APint(16);//2 bytes
	unsigned char bytes[2]={0b00010111,0b01010011};//arbitrary pattern that is easy to see if there are order errors
	string got,expected=getBinString(bytes[0])+getBinString(bytes[1]);//match print order to the string (left: 0, right: n)
	bigint.insertByte(bytes[0],1);//reverse the assignment order since the assignment and printing order are reversed
	bigint.insertByte(bytes[1],0);
	got=bigint.dumpBinString();
	if(formatBinString(expected)==formatBinString(got)){//if they match
		cout<<"String matches what is expected"<<endl;//if not silenced, print success
		return 0;//flag success
	}else{//if there is a mismatch
		cout<<"Mismatch in the input vs the expected output."<<endl;
		cout<<"Expected: "<<formatBinString(expected)<<endl;
		cout<<"Got     : "<<formatBinString(got)<<endl;
		return 1;//flag an error
	}
}
/**
 * Test the ability to read and write bytes directly into the integer structure
 * @return 0 upon success, anything else is a failure
 */
int test_byteReadWrite(){
	cout<<"Testing the APInt byte insertion and recall functions"<<endl;//print test name if not silenced
	APint bigint=APint(64);//arbitrary size
	unsigned char byte=0b11001001;//arbitrary pattern that is easy to check for errors
	for(APint::precisionType i=0; i<bigint.getSize(); ++i){//loop over all bytes of the bigint object
		unsigned char got;
		bigint.zeroOut();//blank out the object
		bigint.insertByte(byte,i);//write the expected value
		for(APint::precisionType j=0; j<bigint.getSize(); ++j){//read each byte
			got=bigint.recallByte(j);
			if(i!=j && got!=0){//fail if a byte other than the one we wrote is non-zero
				cout<<"Assigned byte "<<i<<": byte "<<j<<": Expected 00000000, got: "<<getBinString(got)<<endl;
				cout<<"Raw Int: "<<formatBinString(bigint.dumpBinString())<<endl;
				return 1;//flag an error
			}else if(i==j && got!=byte){//fail if the written byte was altered
				cout<<"Assigned byte "<<i<<": byte "<<j<<": Expected "<<getBinString(byte)<<", got: "<<getBinString(got)<<endl;
				cout<<"Raw Int: "<<formatBinString(bigint.dumpBinString())<<endl;
				return 1;//flag an error
			}
		}
	}
	return 0;//return success if we complete the test
}