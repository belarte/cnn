add_executable(test_network test.cpp)
linkTestLibraries(test_network)

add_test(
	NAME Network
	COMMAND test_network
)
