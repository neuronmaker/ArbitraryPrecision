//
// File: ArbitraryPrecisionInt.h
// Project: Arbitrary Precision
// Created by Dalton Herrewynen on Feb 6 2023.
//
#ifndef BITS_IN_BYTE
//if we do not have the number of bits in a byte defined
#define BITS_IN_BYTE 8
//makes it easier to set to systems that assign other than 8bits per byte
#endif

#ifndef ARBITRARYPRECISION_ARBITRARYPRECISIONINT_H
#define ARBITRARYPRECISION_ARBITRARYPRECISIONINT_H

//how many bits should the default size be?
#define DEFAULT_INT_SIZE 128

class APint {//this is the implementation of integers
    typedef unsigned int precisionType;//for easy changing down the road
public:
    // constructors
    APint();
    APint(precisionType newSize);

    ~APint();//default destructor
    // operators

    // conversions

private:
    precisionType sizeInBytes;
    unsigned char* value;//our signed integer stored as an array of bytes (chars)
};

#endif //ARBITRARYPRECISION_ARBITRARYPRECISIONINT_H
