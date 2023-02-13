//
// File: ArbitraryPrecisionFloat.h
// Project: Arbitrary Precision
// Created by Dalton Herrewynen on Feb 6 2023.
//

#ifndef ARBITRARYPRECISION_ARBITRARYPRECISIONFLOAT_H
#define ARBITRARYPRECISION_ARBITRARYPRECISIONFLOAT_H

//making the default precision exactly double that of the usual double data type
#define DEFAULT_PRECISION 16

class APfloat {
public:

    APfloat();//constructors
    APfloat(unsigned int precision);

    APfloat operator+ (APfloat f2);//basic operators for arithmetic
    APfloat operator- (APfloat f2);
    APfloat operator* (APfloat f2);
    APfloat operator/ (APfloat f2);
    APfloat operator% (APfloat f2);

    APfloat operator++ ();//handy operators like incrementing
    APfloat operator-- ();

    APfloat operator= (APfloat f2);//assignment
    APfloat operator+= (APfloat f2);
    APfloat operator-= (APfloat f2);
    APfloat operator*= (APfloat f2);
    APfloat operator/= (APfloat f2);
    APfloat operator%= (APfloat f2);

    APfloat operator== (APfloat f2);//equality and logic
    APfloat operator!= (APfloat f2);
    APfloat operator<= (APfloat f2);
    APfloat operator>= (APfloat f2);
    APfloat operator> (APfloat f2);
    APfloat operator< (APfloat f2);

    double toDouble();//conversions to other data types (sometimes lossy)

private:
    unsigned int precision;//Upon creation these two will be set
    unsigned int exponentSize;//These two are the number of bits that the machine should use for our number

    bool infinity;//special values go here
    unsigned char* fraction;//these pointers are where I store the dynamically allocated bytes to make this magic work
    unsigned char* exponent;//I suspect that using integers might be faster, but I want to show how to do this using raw bytes

};

#endif //ARBITRARYPRECISION_ARBITRARYPRECISIONFLOAT_H
