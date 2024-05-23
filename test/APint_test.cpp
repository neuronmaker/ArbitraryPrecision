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
int test_dumpBinString(); int test_byteReadWrite();
int test_printNumber(); int test_parseString();
int test_addition(); int test_subtraction();
int test_load(); int test_assignment();

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
		else if(argument=="load") retVal=test_load();
		else if(argument=="assignment") retVal=test_assignment();
		else if(argument=="addition") retVal=test_addition();
		else if(argument=="subtraction") retVal=test_subtraction();
		else if(argument=="printNumber") retVal=test_printNumber();
		else if(argument=="parseNumber") retVal=test_parseString();
		else cout<<"Invalid test name: "<<argument<<endl;
		if(retVal==0)
			cout<<"Success!"<<endl;//if the test flags success, print it
	}
	return retVal;
}

/**
 * Test the ability to set the value of an APint object
 * @return 0 for success, anything else is a failure
 */
int test_load(){
	cout<<"Test loading values from a native C++ ints and longs"<<endl;
	APint bigint=APint(128);//be larger than a long
	int testInt;
	long testLong;
	unsigned char expected,got;
	for(int test=0; test<256; ++test){//going to do 256 test patterns
		testInt=test;//copy the test byte to the int and long
		testLong=test;
		testInt=(testInt<<(8*(sizeof(int)-1)))|0b00011000;//copy an arbitrary position finding pattern to the rightmost byte
		testLong=(testLong<<(8*(sizeof(long)-1)))|0b00011000;//move the pattern to the leftmost byte

		bigint.load(testInt);//test loading ints
		for(int i=0; i<sizeof(int); ++i){//check each byte
			got=bigint.recallByte(i);//checking one byte at a time
			expected=getByte(testInt,i);//extract the i'th byte
			if(testInt<0 && i==sizeof(int)-1){//if we are at the final byte of a negative int
				expected&=0b01111111;//remove the sign bit since that will be at the far end of the APint
				//check the last bit of the last byte of the APint
				if(0==(bigint.recallByte(bigint.getSize()-1) & 0b10000000)){
					cout<<"Sign bit was not set"<<endl;
					cout<<"Source int structure: "<<formatBinString(getBinString(testInt))<<endl;
					cout<<"Internal APint structure: "<<formatBinString(bigint.dumpBinString())<<endl;
					return 1;//signal a failed test if the sign bit is not set
				}
			}
			if(expected!=got){//compare the previously masked byte with the contents of the integer structure
				cout<<"Failure at byte "<<i<<", \nExpected: "<<getBinString(expected)<<endl;
				cout<<"Got:      "<< getBinString(got)<<endl;
				cout<<"Source int structure: "<<formatBinString(getBinString(testInt))<<endl;
				cout<<"Internal APint structure: "<<formatBinString(bigint.dumpBinString())<<endl;
				return 1;//if the bytes are not the same, then the test fails
			}
		}

		bigint.load(testLong);//test loading longs
		for(int i=0; i<sizeof(long); ++i){//check each byte
			got=bigint.recallByte(i);//checking one byte at a time
			expected=getByte(testLong,i);//extract the i'th byte
			if(testLong<0 && i==sizeof(long)-1){//if we are at the final byte of a negative long
				expected&=0b01111111;//remove the sign bit since that will be at the far end of the APint
				//check the last bit of the last byte of the APint
				if(0==(bigint.recallByte(bigint.getSize()-1) & 0b10000000)){
					cout<<"Sign bit was not set"<<endl;
					cout<<"Source long structure: "<<formatBinString(getBinString(testLong))<<endl;
					cout<<"Internal APint structure: "<<formatBinString(bigint.dumpBinString())<<endl;
					return 1;//signal a failed test if the sign bit is not set
				}
			}
			if(expected!=got){//compare the previously masked byte with the contents of the integer structure
				cout<<"Failure at byte "<<i<<", \nExpected: "<<getBinString(expected)<<endl;
				cout<<"Got:      "<< getBinString(got)<<endl;
				cout<<"Source long structure: "<<formatBinString(getBinString(testLong))<<endl;
				cout<<"Internal APint structure: "<<formatBinString(bigint.dumpBinString())<<endl;
				return 1;//if the bytes are not the same, then the test fails
			}
		}
	}
	return 0;//if we get to the end, the test has passed
}

/**
 * Test assignment operator
 * @return 0 for success, 1 for failure
 */
int test_assignment(){
	cout<<"Testing the assignment operator"<<endl;
	APint original=APint(64), copy;
	for(int test=0; test<256; ++test){//testing every possible value that a byte can hold
		original.zeroOut();//blank out the structure to begin with
		for(int i=0; i<original.getSize(); ++i){//repeat the test pattern across the structure
			original.insertByte((unsigned char) test,i);//write the test pattern to each address
		}
		copy=original;//perform the assignment
		for(int i=0; i<original.getSize(); ++i){
			if(copy.recallByte(i)!=original.recallByte(i)){//if the copy and original do not match
				cout<<"Failure at byte "<<i<<" Expected: "<<getBinString(original.recallByte(i))
					<<" Got: "<<getBinString(copy.recallByte(i))<<endl;
				cout<<"Original: "<<formatBinString(original.dumpBinString())<<endl;
				cout<<"Copy    : "<<formatBinString(copy.dumpBinString())<<endl;
				cout<<"Test Pattern: "<<getBinString((unsigned char) test)<<endl;
				return 1;
			}
		}
	}
	return 0;
}

/**
 * Test for correct addition
 * @return 0 for success, anything else is a failure
 */
int test_addition(){
	cout<<"Testing for correct addition operations"<<endl;
	APint left=APint(sizeof(int)*8), right=APint(sizeof(int)*8);//test on a small scale, equal to an int

	APint result;//holder for the results
	//test basic addition (does not carry from byte to byte)

	//todo test addition that overflows from one data element to the next
	return 0;
}

/**
 * Test for correct subtraction
 * @return 0 for success, anything else is a failure
 */
int test_subtraction(){
	cout<<"Testing for correct subtraction"<<endl;
	APint left=APint(16), right=APint(16);//test on a small (16 bit) scale
	APint result;//holder for the results
	return 0;
}

/**
 * Tests printing the integer as a human-readable number
 * @return 0 for success, anything else is a failure
 */
int test_printNumber(){
	cout<<"Testing the ability of the APInt to print a human-readable number"<<endl;
	APint bigint=APint(16);//2 bytes
	return 0;
}
/**
 * Tests parsing a number from a string
 * @return 0 for success, anything else is a failure
 */
int test_parseString(){
	cout<<"Testing the ability of the APInt to read a number from a string"<<endl;
	APint bigint=APint(16);//2 bytes
	return 0;
}
/**
 * Test the ability to print the binary data from the integer structure as a string
 * @return 0 for success, anything else is a failure
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
 * @return 0 for success, anything else is a failure
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