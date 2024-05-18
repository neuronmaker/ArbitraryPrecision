//
// File: ArbitraryPrecisionFloat.cpp
// Project: Arbitrary Precision
// Created by Dalton Herrewynen on Feb 6 2023.
//

// There are many ways to do this, I am implementing this version using a series of bits and directly manipulating them
// Computers use scientific notation for floating point math, Mantissa (fraction) and exponent are stored
// Mantissa/fraction may only be a few bits but can represent a large or small number based on the exponent
// e.g. 12345.654321 = 1.2345654321 * 10^4 and 1234.56789 = 1.23456789 * 10^3
// Computers do this with binary numbers and I will make this work with a large string of bits
// I once thought to do this using a series of integer types, but I want to show how it's done using only binary data (chars).

#include "APfloat.h"

APfloat::APfloat() :APfloat(DEFAULT_FLOAT_PRECISION){//delegated constructor call
}

APfloat::APfloat(precisionType givenPrecision) :APfloat(givenPrecision, 0.25*givenPrecision){//delegated constructor call with bad floor rounding
}

APfloat::APfloat(precisionType givenPrecision,
				 precisionType givenExponentSize){//specified sized are in bits, Must convert them to bytes first
	precision=getByteCount(givenPrecision);//we want bytes and are given bits, fix that
	exponentSize=getByteCount(givenExponentSize);
	fraction=new unsigned char[precision];//ask for memory
	exponent=new unsigned char[exponentSize];
	infinity=false;//set edge cases to false
	NaN=false;// Will set the value to 0.0, so it will be a real number
	positiveSign=true;//initial value is +0.0
}

APfloat::~APfloat(){//default destructor
	delete[] exponent;//ensure deletion of exponent and fraction
	delete[] fraction;
	exponent=nullptr;//set to null to avoid dangling pointers
	fraction=nullptr;
}

APfloat APfloat::operator+(APfloat &f1){
	//add this->stuff to f1.stuff
	return APfloat();
}

APfloat APfloat::operator-(APfloat &f1){
	return APfloat();
}

APfloat APfloat::operator*(APfloat &f1){
	return APfloat();
}

APfloat APfloat::operator/(APfloat &f1){
	return APfloat();
}

APfloat APfloat::operator=(APfloat &f1){
	return APfloat();
}

APfloat APfloat::operator+=(APfloat &f1){
	return APfloat();
}

APfloat APfloat::operator-=(APfloat &f1){
	return APfloat();
}

APfloat APfloat::operator*=(APfloat &f1){
	return APfloat();
}

APfloat APfloat::operator/=(APfloat &f1){
	return APfloat();
}

bool APfloat::operator==(APfloat &f1){
	return false;
}

bool APfloat::operator!=(APfloat &f1){
	return false;
}

bool APfloat::operator<=(APfloat &f1){
	return false;
}

bool APfloat::operator>=(APfloat &f1){
	return false;
}

bool APfloat::operator>(APfloat &f1){
	return false;
}

bool APfloat::operator<(APfloat &f1){
	return false;
}

unsigned int getByteCount(unsigned int bits){
	//typically, there are 8 bits in a byte, I am using a #define so that I can support weird architectures that don't use 8bit bytes
	if(bits%BITS_IN_BYTE==0)
		return (bits/BITS_IN_BYTE);//integer division truncates, for divisible by 8 values this is fine
	else
		return (bits/BITS_IN_BYTE)+
			   1;//complex way to say, add an extra byte if the number is between two byte counts, ceiling rounding.
}
