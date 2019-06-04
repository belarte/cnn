#include "matrices.h"
#include "test/assert.h"

#include <iostream>

void comparison()
{
	Matrix<2, 3> m1;
	Matrix<2, 3> m2{ {{ {1, 2}, {3, 4}, {5, 6} }} };
	Matrix<2, 3> m3{ {{ {1, 2}, {3, 4}, {5, 6} }} };
	Matrix<2, 3> m4{ {{ {1, 2}, {3, 3}, {5, 6} }} };

	ASSERT(m2 == m3);
	ASSERT(m3 == m2);

	ASSERT(m1 != m2);
	ASSERT(m2 != m4);
	ASSERT(m3 != m4);
	ASSERT(m4 != m1);
}

void addition()
{
	Matrix<2, 3> m1;
	Matrix<2, 3> m2{ {{ {1, 2}, {2, 3}, {3, 4} }} };
	Matrix<2, 3> m3{ {{ {1, 2}, {2, 3}, {3, 4} }} };
	Matrix<2, 3> m4{ {{ {1, 2}, {2, 1}, {2, 2} }} };
	Matrix<2, 3> m5{ {{ {2, 4}, {4, 4}, {5, 6} }} };

	ASSERT(m2 + m1 == m2);
	ASSERT(m1 + m3 == m2);
	ASSERT(m2 + m4 == m5);
	ASSERT(m3 + m4 == m5);
	ASSERT(m2 + m4 == m3 + m4);
	ASSERT(m2 + m4 + m1 == m3 + m4);
}

void substraction()
{
	Matrix<2, 3> m1;
	Matrix<2, 3> m2{ {{ {1, 2}, {2, 3}, {3, 4} }} };
	Matrix<2, 3> m3{ {{ {1, 2}, {2, 3}, {3, 4} }} };
	Matrix<2, 3> m4{ {{ {1, 2}, {2, 1}, {2, 2} }} };

	Matrix<2, 3> m5{ {{ {0, 0}, {0, 2}, {1, 2} }} };
	Matrix<2, 3> m6{ {{ {0, 0}, {0, -2}, {-1, -2} }} };

	ASSERT(m2 - m1 == m2);
	ASSERT(m2 - m3 == m1);
	ASSERT(m2 - m4 == m5);
	ASSERT(m4 - m3 == m6);
	ASSERT(m2 - m4 == m3 - m4);
	ASSERT(m2 - m4 - m1 == m3 - m4);
}

void multiplication()
{
	Matrix<2, 3> m1{ {{ {1, 2}, {3, 4}, {5, 6} }} };
	Matrix<3, 2> m2{ {{ {1, 2, 3}, {4, 5, 6} }} };
	Matrix<3, 3> m3{ {{ {9, 12, 15}, {19, 26, 33}, {29, 40, 51} }} };
	Matrix<2, 2> m4{ {{ {22, 28}, {49, 64} }} };

	ASSERT_EQ(m1 * m2, m3);
	ASSERT_EQ(m2 * m1, m4);
}

void scalar_multiplication()
{
	Matrix<2, 3> m1;
	Matrix<2, 3> m2{ {{ {1, 2}, {2, 3}, {3, 4} }} };
	Matrix<2, 3> m3{ {{ {2, 4}, {4, 6}, {6, 8} }} };

	ASSERT_EQ(3 * m1, m1);
	ASSERT_EQ(2 * m2, m3);
	ASSERT_EQ(2u * m2, m3);
}

void transpose()
{
	Matrix<2, 3> m1{ {{ {1, 2}, {3, 4}, {5, 6} }} };
	Matrix<3, 2> m2{ {{ {1, 3, 5}, {2, 4, 6} }} };

	ASSERT_EQ(m1.transpose(), m2);
	ASSERT_EQ(m2.transpose(), m1);
}

int main(int, char**)
{
	std::cout << "Start testing..." << std::endl;

	comparison();
	addition();
	substraction();
	multiplication();
	scalar_multiplication();
	transpose();

	std::cout << "Done!" << std::endl;
	return 0;
}
