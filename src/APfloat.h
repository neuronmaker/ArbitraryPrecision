//
// File: ArbitraryPrecisionFloat.h
// Project: Arbitrary Precision
// Created by Dalton Herrewynen on Feb 6 2023.
//
#ifndef BITS_IN_BYTE
//if we do not have the number of bits in a byte defined
#define BITS_IN_BYTE 8
//makes it easier to set to systems that assign other than 8bits per byte
#endif

#ifndef ARBITRARYPRECISION_APFLOAT_H
#define ARBITRARYPRECISION_APFLOAT_H

//making the default precision exactly double that of the usual double data type
#define DEFAULT_FLOAT_PRECISION 128 //Note that this is in bits

/**
 * Arbitrary precision floating point
 * @author Dalton Herrewynen
 * @copyright All rights reserved
 * @version 0.1
 */
class APfloat{
	typedef unsigned int precisionType;//for easy changing down the road
	typedef unsigned char fractionType, exponentType;
public:

	APfloat();//constructors
	APfloat(precisionType givenPrecision);
	APfloat(precisionType givenPrecision, precisionType givenExponentSize);

	~APfloat();//destructor

	//todo create destructor, Create enum for NaN, Infinity, etc., catch divide by 0

	APfloat operator+(APfloat &);//basic operators for arithmetic
	APfloat operator-(APfloat &);

	APfloat operator*(APfloat &);

	APfloat operator/(APfloat &);

	APfloat operator=(APfloat &);//assignment
	APfloat operator+=(APfloat &);

	APfloat operator-=(APfloat &);

	APfloat operator*=(APfloat &);

	APfloat operator/=(APfloat &);

	//consider inlining most of these
	bool operator==(APfloat &);//equality and logic
	bool operator!=(APfloat &);//this one may be redundant as teh compiler may or may not generate this one for me
	bool operator<=(APfloat &);

	bool operator>=(APfloat &);

	bool operator>(APfloat &);

	bool operator<(APfloat &);

	//conversions to other data types (sometimes lossy)

private:
	//Note that these are stored as bytes not bits
	precisionType precision;//total precision
	precisionType exponentSize;//size of exponent

	bool infinity, NaN;//special values go here
	bool positiveSign;//true for positive, false for negative
	fractionType *fraction;//these pointers are where I store the dynamically allocated bytes to make this magic work
	exponentType *exponent;//I suspect that using integers might be faster, but I want to show how to do this using raw bytes

};

#endif ARBITRARYPRECISION_APFLOAT_H

//to make things easier for users, this function divides bits by 8 to get number of bytes for this library
//if a user wants to get precision to 71 bits, that is not possible here, so this will round to the nearest byte
unsigned int getByteCount(unsigned int bits);//ensure this matches the chosen type for precision
// make this live in the class or make the typedef live outside the class later
