//
// File: ArbitraryPrecisionFloat.h
// Project: Arbitrary Precision
// Created by Dalton Herrewynen on Feb 6 2023.
//

//There are many ways to do this, I am implementing this version using a series of bits and directly manipulating them
//Computers use scientific notation for floating point math, Mantissa and exponent are stored
//Mantissa may only be a few bits but can represent a large or small number based on the exponent
//e.g. 12345.654321 = 1.2345654321 * 10^4 and 1234.56789 = 1.23456789 * 10^3
//Computers do this with binary numbers and I will make this work with a large string of bits
//I once thought to do this using a series of integer types but I want to show how it's done using only binary data

#include "ArbitraryPrecisionFloat.h"

APfloat APfloat::operator+(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator-(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator*(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator/(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator%(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator++() {
    return APfloat();
}

APfloat APfloat::operator--() {
    return APfloat();
}

APfloat APfloat::operator=(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator+=(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator-=(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator*=(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator/=(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator%=(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator==(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator!=(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator<=(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator>=(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator>(APfloat f2) {
    return APfloat();
}

APfloat APfloat::operator<(APfloat f2) {
    return APfloat();
}
