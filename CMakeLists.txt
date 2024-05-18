cmake_minimum_required(VERSION 3.24)
project(ArbitraryPrecision)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

set(APP_ROOT ${CMAKE_SOURCE_DIR}/src)
set(TEST_ROOT ${CMAKE_SOURCE_DIR}/test)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories(${APP_ROOT})

set(
		APLIB_FILES
		${APP_ROOT}/APInt.h
		${APP_ROOT}/APInt.cpp
		${APP_ROOT}/APFloat.h
		${APP_ROOT}/APFloat.cpp

)

set(
		SOURCE_FILES
		${APP_ROOT}/main.cpp
)

set(
		TEST_FILES
		${TEST_ROOT}/test_utils.cpp
		${TEST_ROOT}/test_utils.h
)

add_executable(ArbitraryPrecision ${SOURCE_FILES} ${APLIB_FILES})

#Unit testing
add_executable(APInt_test ${TEST_ROOT}/APInt_test.cpp ${APLIB_FILES}  ${TEST_FILES})
add_test(Test_Integer_BinString, "${CMAKE_SOURCE_DIR}/bin/APInt_test" "-p" "dumpBinString")
add_test(Test_Integer_constructors, "${CMAKE_SOURCE_DIR}/bin/APInt_test" "-p" "byteReadWrite")
add_test(Test_Integer_constructors, "${CMAKE_SOURCE_DIR}/bin/APInt_test" "-p" "printNumber")
add_test(Test_Integer_constructors, "${CMAKE_SOURCE_DIR}/bin/APInt_test" "-p" "parseString")

add_executable(APFloat_test ${TEST_ROOT}/APFloat_test.cpp ${APLIB_FILES} ${TEST_FILES})
#add_test(Test_Float_0, "${CMAKE_SOURCE_DIR}/bin/APFloat_test" "-p" "0")

add_executable(ArbitraryPrecision_main_test ${TEST_ROOT}/main_test.cpp ${APLIB_FILES} ${TEST_FILES})
#add_test(Test_main_0, "${CMAKE_SOURCE_DIR}/bin/ArbitraryPrecision_main_test" "-p" "0")