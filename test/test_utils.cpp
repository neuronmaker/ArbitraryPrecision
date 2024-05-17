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
 * @param byte The unsigned char to check
 * @return a printable string of 0's and 1's
 */
std::string getBinString(unsigned char byte){
	std::string result;
	for(int i=7; i>=0; --i){//print in reverse since we represent bits right to left and print them left to right
		if(0!=(byte & (1 << i)))//figure out if this bit is a 1 or a 0
			result+='1';
		else
			result+='0';
	}
	return result;
}