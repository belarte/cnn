#include "matrices.h"
#include <iostream>

int main(int, char**)
{
	Matrix<2, 3> m1;
	Matrix<2, 3> m2{ {{ {1, 2}, {3, 4}, {5, 6} }} };
	std::cout << "m1:\n" << m1 << "\nm2:\n" << m2 << std::endl;
	return 0;
}
