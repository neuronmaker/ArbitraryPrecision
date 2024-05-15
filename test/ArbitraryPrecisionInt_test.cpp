//
// File: ArbitraryPrecisionInt_test.cpp
// Project: Arbitrary Precision math library
// Created by Dalton Herrewynen on May 15, 2024
//
#include "test_utils.h"
#include "ArbitraryPrecisionInt.h"
#include <string>
#include <iostream>

using namespace std;
//declarations
int test_dumpBinString(bool print); int test_byteReadWrite(bool print);

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
	int retVal=0;
	for(int i=2; i<argNum && retVal==0; ++i){//loop over all arguments unless one or more tests fail
		argument=args[i];
		if(argument=="dumpBinString") retVal=test_dumpBinString(print);
		else if(argument=="byteReadWrite") retVal=test_byteReadWrite(print);
		else invalidTest(argument);
	}
	return retVal;
}

int test_dumpBinString(bool print){
	if(print) cout<<"Testing the APInt dumpBinString() function"<<endl;//print test name if not silenced
	APint bigint=APint(16);//2 bytes
	string got,expected="00010111 01010011";//arbitrary pattern that is easy to see if there are order errors
	unsigned char bytes[2]={0b00010111,0b01010011};//make sure these patterns match the expected string
	bigint.insertByte(bytes[0],1);//reversed order since they are stored opposite of print order... todo consider changing this or writing an interface
	bigint.insertByte(bytes[1],0);
	got=bigint.dumpBinString();
	//bigint
	if(formatBinString(expected)==formatBinString(got)){//if they match
		if(print) cout<<"String matches what is expected"<<endl;//if not silenced, print success
		return 0;//flag success
	}else{//if there is a mismatch
		if(print){//if not silenced, print where the error happened
			cout<<"Mismatch in the input vs the expected output."<<endl;
			cout<<"Expected: "<<formatBinString(expected)<<endl;
			cout<<"Got     : "<<formatBinString(got)<<endl;
		}
		return 1;//flag an error
	}
}

int test_byteReadWrite(bool print){
	if(print) cout<<"Testing the APInt byte insertion and recall functions"<<endl;//print test name if not silenced
	APint bigint=APint(64);//arbitrary size
	unsigned char byte=0b11001001;//arbitrary pattern that is easy to check of errors
	for(APint::precisionType i=0; i<bigint.getSize(); ++i){//loop over all bytes of the bigint object
		unsigned char got;
		bigint.zeroOut();//blank out the object
		bigint.insertByte(byte,i);//write the expected value
		for(APint::precisionType j=0; j<bigint.getSize(); ++j){//read each byte
			got=bigint.recallByte(j);
			if(i!=j && got!=0){//fail if a byte other than the one we wrote is non-zero
				if(print){
					cout<<"Assigned byte "<<i<<": byte "<<j<<": Expected 00000000, got: "<<getBinString(got)<<endl;
					cout<<"Raw Int: "<<formatBinString(bigint.dumpBinString())<<endl;
				}
				return 1;//flag an error
			}else if(i==j && got!=byte){//fail if the written byte was altered
				if(print){
					cout<<"Assigned byte "<<i<<": byte "<<j<<": Expected "<<getBinString(byte)<<", got: "<<getBinString(got)<<endl;
					cout<<"Raw Int: "<<formatBinString(bigint.dumpBinString())<<endl;
				}
				return 1;//flag an error
			}
		}
	}
	return 0;//return success if we complete the test
}