#include "matrices.h"
#include <iostream>

#define ASSERT(cond) \
   do { \
      if (!(cond)) { \
         std::cerr << "Error in file " << __FILE__ << ":" << __LINE__; \
			std::cerr << " in function " << __func__ << "() => " << #cond << std::endl; \
		} \
   } while(0)

#define ASSERT_EQ(left, right) \
   do { \
      if (!(left == right)) { \
         std::cerr << "Error in file " << __FILE__ << ":" << __LINE__; \
			std::cerr << " in function " << __func__ << "() => " << #left << " != " << #right; \
			std::cerr << "\nwith " << #left << " =\n" << left; \
			std::cerr << "and " << #right << " =\n" << right; \
		} \
   } while(0)

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

int main(int, char**)
{
	comparison();
	addition();
	multiplication();
	scalar_multiplication();

	std::cerr << "Done testing!" << std::endl;
	return 0;
}
