add_executable(test_random test.cpp)
linkTestLibraries(test_random)

add_test(
	NAME Random
	COMMAND test_random
)
