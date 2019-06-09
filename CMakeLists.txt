cmake_minimum_required(VERSION 3.12.0)

project(CNN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(.)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_matrix matrices/test.cpp)
target_link_libraries(test_matrix ${GTEST_BOTH_LIBRARIES} pthread)

add_executable(test_network network/test.cpp)
target_link_libraries(test_network ${GTEST_BOTH_LIBRARIES} pthread)

add_test(
	NAME Matrices
	COMMAND test_matrix
)

add_test(
	NAME Network
	COMMAND test_network
)
