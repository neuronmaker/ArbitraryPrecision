//
// File: ArbitraryPrecisionFloat.h
// Project: Arbitrary Precision
// Created by Dalton Herrewynen on Feb 6 2023.
//

#ifndef ARBITRARYPRECISION_ARBITRARYPRECISIONFLOAT_H
#define ARBITRARYPRECISION_ARBITRARYPRECISIONFLOAT_H


class APfloat {
public:
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
private:
    unsigned int precision;//Upon creation these two will be set
    unsigned int exponentSize;//These two are the number of bits that the machine should use for our number

};


#endif //ARBITRARYPRECISION_ARBITRARYPRECISIONFLOAT_H
