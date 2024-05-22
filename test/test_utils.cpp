//
// File: test_utils.cpp
// Project: Arbitrary Precision math library
// Created by Dalton Herrewynen on May 15, 2024
//

#include "test_utils.h"

/**
 * Formats a string of 1's and 0's for consistent comparisons in this test
 * @param src A string to reformat
 * @return Consistent but readable string of 1's and 0's
 */
std::string formatBinString(std::string src){
	std::string result;
	unsigned int digits=0;
	for(unsigned int i=0; i<src.length(); ++i){//loop over every character
		if(src.at(i)=='1' || src.at(i)=='0'){//only copy 0's and 1's
			result+=src.at(i);
			++digits;//count how many digits there are
			if(digits%8==0)//every 8 digits, insert a space for readability
				result+=' ';
		}
	}
	if(result.at(result.length()-1)==' ')//if the last character is a space, drop it
		result.pop_back();
	return result;
}

/**
 * Returns a printable string showing the 0's and 1's of the provided data type
 * @param value The value to convert into a binary string
 * @return a printable string of 0's and 1's
 */
std::string getBinString(unsigned char value){
	std::string result;
	for(int i=7; i>=0; --i){//print in reverse since we represent bits right to left and print them left to right
		if(0!=(value & (1 << i)))//figure out if this bit is a 1 or a 0
			result+='1';
		else
			result+='0';
	}
	return result;
}
/**
 * Returns a printable string showing the 0's and 1's of the provided data type
 * @param value The value to convert into a binary string
 * @return a printable string of 0's and 1's
 */
std::string getBinString(int value){
	std::string result;
	for(int i=31; i>=0; --i){//32 bits in an int, so from 31 through 0 inclusive
		if(0!=(value & (1 << i)))//figure out if this bit is a 1 or a 0
			result+='1';
		else
			result+='0';
	}
	return result;
}
/**
 * Returns a printable string showing the 0's and 1's of the provided data type
 * @param value The value to convert into a binary string
 * @return a printable string of 0's and 1's
 */
std::string getBinString(long value){
	std::string result;
	for(int i=63; i>=0; --i){//64 bits in a long, so from 63 through 0 inclusive
		if(0!=(value & (1L << i)))//figure out if this bit is a 1 or a 0
			result+='1';
		else
			result+='0';
	}
	return result;
}
