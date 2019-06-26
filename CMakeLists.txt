cmake_minimum_required(VERSION 3.12.0)

project(CNN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

include_directories(.)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

function(linkTestLibraries exec)
	target_link_libraries(${exec} ${GTEST_BOTH_LIBRARIES} pthread)
endfunction()

add_subdirectory(app)
add_subdirectory(math)
add_subdirectory(matrices)
add_subdirectory(network)
