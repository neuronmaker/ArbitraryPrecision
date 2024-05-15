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

#ifndef ARBITRARYPRECISION_ARBITRARYPRECISIONINT_H
#define ARBITRARYPRECISION_ARBITRARYPRECISIONINT_H

#include <string>

//how many bits should the default size be?
#define DEFAULT_INT_SIZE 128
//constants relating to what datatype is used to store the value
#define APInt_VAL_SIZE 8
#define APIntValMax 255
//Change below if using a data type with more bits
#define APIntSignBit 0b1000000

/**
 * Arbitrary precision integer
 * @author Dalton Herrewynen
 * @copyright All rights reserved
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
	//operators
	friend APint operator+(const APint &, const APint &);//make these non-members
	friend APint operator-(const APint &, const APint &);

	APint &operator=(APint &);//handle assignment
	//conversions
	std::string dumpString();
	std::string dumpBinString();

	void loadVal(valueType hex[], precisionType len);

	void zeroOut();
	//for testing and troubleshooting
	void insertByte(valueType val,precisionType index);
	valueType recallByte(precisionType index);
	precisionType getSize();
};

#endif //ARBITRARYPRECISION_ARBITRARYPRECISIONINT_H
