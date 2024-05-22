//
// File: test_utils.h
// Project: Arbitrary Precision math library
// Created by Dalton Herrewynen on May 15, 2024
//

#ifndef ARBITRARYPRECISION_TEST_UTILS_H
#define ARBITRARYPRECISION_TEST_UTILS_H
#include <string>

std::string formatBinString(std::string);
std::string getBinString(unsigned char value);
std::string getBinString(int value);
std::string getBinString(long value);

unsigned char getByte(long value,int index);
unsigned char getByte(int value,int index);

#endif
