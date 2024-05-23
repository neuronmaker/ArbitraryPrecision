//
// File: ArbitraryPrecisionInt.h
// Project: Arbitrary Precision
// Created by Dalton Herrewynen on Feb 6 2023.
//
#ifndef BITS_IN_BYTE
//if we do not have the number of bits in a byte defined
#define BITS_IN_BYTE 8
//makes it easier to set to systems that assign other than 8 bits per byte
#endif

#ifndef ARBITRARYPRECISION_APINT_H
#define ARBITRARYPRECISION_APINT_H

#include <string>

//how many bits should the default size be?
#define DEFAULT_INT_SIZE 128
//Constants for the data type used to store the internal structure
#define APint_VAL_SIZE 8 //currently using bytes (unsigned chars)
#define APintValMax 255
#define APintSignBit 0b10000000
#define APintValMask 0b11111111 //8 1's are used for a byte sized data type
//how bytes does each C++ datatype take to store
#define IntegerBytes 4
#define LongBytes 8

/**
 * Arbitrary precision integer (signed)
 * @author Dalton Herrewynen
 * @version 0.1
 */
class APint{
public:
	typedef unsigned int precisionType;//for easy changing down the road
	typedef unsigned char valueType;//Store our signed integer value as an array of bytes (chars)
private:
	bool overflow;//flag this as true if we overflow or underflow
	precisionType sizeInBytes;//bytes are the smallest unit of memory the computer can use
	//basic structure (b is a bit): MSB bbbb bbbb <- bbbb bbbb LSB
	//MSB value[n] <- value[0] LSB
	valueType *value;//our signed integer stored as an array of bytes (chars)
public:
	//constructors
	APint();
	APint(precisionType newSize);

	~APint();//default destructor
	bool isOverflow();
	precisionType getSize();
	//operators
	friend APint operator+(const APint &, const APint &);//make these non-members
	friend APint operator-(const APint &, const APint &);

	APint &operator=(APint &);//handle assignment
	//conversions
	void loadVal(valueType hex[], precisionType len);
	bool load(int);//load functions to import C++ native datatypes
	bool load(long);

	void zeroOut();
	std::string to_string();
	//for testing and troubleshooting
	std::string dumpBinString();
	void insertByte(unsigned char val,precisionType index);
	unsigned char recallByte(precisionType index);
};

#endif
