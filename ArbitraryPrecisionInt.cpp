//
// File: ArbitraryPrecisionInt.cpp
// Project: Arbitrary Precision
// Created by Dalton Herrewynen on Feb 6 2023.
//

#include "ArbitraryPrecisionInt.h"

APint::APint() {
    APint(DEFAULT_INT_SIZE);//set it to the default integer size
}

APint::APint(APint::precisionType newSize) {//size is in bits, round up to next byte
    if(newSize%BITS_IN_BYTE==0) newSize=newSize/BITS_IN_BYTE;//if divisible (usually by 8 bits per byte)
    else newSize=newSize/BITS_IN_BYTE+1;//add another byte if between two byte sizes... bad ceiling rounding

    sizeInBytes=newSize;//store the total size
    value=new unsigned char[sizeInBytes];//ask for memory
}

APint::~APint() {
    delete[] value;//delete to avoid memory leaks (ensure memory can be re-used when finished with it)
    value= nullptr;//set to null pointer to avoid dangling references
}