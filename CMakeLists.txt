cmake_minimum_required(VERSION 3.24)
project(ArbitraryPrecision)

set(CMAKE_CXX_STANDARD 17)
set(APP_ROOT .)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#set(EXECUTABLE_OUTPUT_PATH ./build)
include_directories(${APP_ROOT})

set(
		SOURCE_FILES
		main.cpp
		${APP_ROOT}/ArbitraryPrecisionInt.h
		${APP_ROOT}/ArbitraryPrecisionInt.cpp
		${APP_ROOT}/ArbitraryPrecisionFloat.h
		${APP_ROOT}/ArbitraryPrecisionFloat.cpp
)

add_executable(ArbitraryPrecision ${SOURCE_FILES})
