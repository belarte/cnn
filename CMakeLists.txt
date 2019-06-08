cmake_minimum_required(VERSION 3.12.0)

project(CNN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(.)

add_executable(test_matrix matrices/test.cpp)
add_executable(test_network network/test.cpp)

enable_testing()

add_test(
	NAME Matrices
	COMMAND test_matrix
)

add_test(
	NAME Network
	COMMAND test_network
)
