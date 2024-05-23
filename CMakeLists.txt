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
		${APP_ROOT}/APint.h
		${APP_ROOT}/APint.cpp
		${APP_ROOT}/APfloat.h
		${APP_ROOT}/APfloat.cpp

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
add_executable(APint_test ${TEST_ROOT}/APint_test.cpp ${APLIB_FILES}  ${TEST_FILES})
add_test(APint_Test_BinString, "${CMAKE_SOURCE_DIR}/bin/APint_test" "dumpBinString")
add_test(APint_Test_ByteReadWrite, "${CMAKE_SOURCE_DIR}/bin/APint_test" "byteReadWrite")
add_test(APint_Test_Load, "${CMAKE_SOURCE_DIR}/bin/APint_test" "load")
add_test(APint_Test_Load, "${CMAKE_SOURCE_DIR}/bin/APint_test" "assignment")
add_test(APint_Test_Addition, "${CMAKE_SOURCE_DIR}/bin/APint_test" "addition")
add_test(APint_Test_Subtraction, "${CMAKE_SOURCE_DIR}/bin/APint_test" "subtraction")
#add_test(APint_Test_PrintNumber, "${CMAKE_SOURCE_DIR}/bin/APint_test" "printNumber")
#add_test(APint_Test_ParseString, "${CMAKE_SOURCE_DIR}/bin/APint_test" "parseString")

#add_executable(APFloat_test ${TEST_ROOT}/APfloat_test.cpp ${APLIB_FILES} ${TEST_FILES})
#add_test(Test_Float_0, "${CMAKE_SOURCE_DIR}/bin/APFloat_test" "0")

add_executable(ArbitraryPrecision_main_test ${TEST_ROOT}/main_test.cpp ${APLIB_FILES} ${TEST_FILES})
#add_test(Test_main_0, "${CMAKE_SOURCE_DIR}/bin/ArbitraryPrecision_main_test" "0")