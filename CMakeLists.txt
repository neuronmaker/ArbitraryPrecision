cmake_minimum_required(VERSION 3.24)
project(ArbitraryPrecision)

set(CMAKE_CXX_STANDARD 17)

add_executable(ArbitraryPrecision main.cpp ArbitraryPrecisionInt.cpp ArbitraryPrecisionInt.h ArbitraryPrecisionFloat.cpp ArbitraryPrecisionFloat.h)
