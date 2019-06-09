add_executable(test_matrix test.cpp)
linkTestLibraries(test_matrix)

add_test(
	NAME Matrices
	COMMAND test_matrix
)
