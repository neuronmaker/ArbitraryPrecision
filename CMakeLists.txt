cmake_minimum_required(VERSION 3.24)
project(ArbitraryPrecision)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(APP_ROOT ./src)
set(TEST_ROOT ./test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories(${APP_ROOT})

set(
		APLIB_FILES
		${APP_ROOT}/ArbitraryPrecisionInt.h
		${APP_ROOT}/ArbitraryPrecisionInt.cpp
		${APP_ROOT}/ArbitraryPrecisionFloat.h
		${APP_ROOT}/ArbitraryPrecisionFloat.cpp

)

set(
		SOURCE_FILES
		${APP_ROOT}/main.cpp
)

set(
		TEST_FILES
		${TEST_ROOT}/ArbitraryPrecisionInt_test.cpp
)

add_executable(ArbitraryPrecision ${SOURCE_FILES} ${APLIB_FILES})

add_executable(ArbitraryPrecision_test ${TEST_FILES} ${APLIB_FILES})

add_test(Test_0, "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}_test" "0")