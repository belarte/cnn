#include "matrices.h"

#include "gtest/gtest.h"

TEST(Matrix, zero_init)
{
	Matrix<2, 3> m;

	for (size_t j=0; j<3; ++j) {
		for (size_t i=0; i<2; ++i) {
			ASSERT_EQ(0, m(i, j));
		}
	}
}

TEST(Matrix, random_init)
{
	int min = 5;
	int max = 10;
	RandomGenerator gen(min, max);
	Matrix<2, 3> m{ gen };

	for (size_t j=0; j<3; ++j) {
		for (size_t i=0; i<2; ++i) {
			auto val = m(i, j);
			ASSERT_GE(val, min);
			ASSERT_LE(val, max);
		}
	}
}

TEST(Matrix, comparison)
{
	Matrix<2, 3> m1;
	Matrix<2, 3> m2{ {{ {1, 2}, {3, 4}, {5, 6} }} };
	Matrix<2, 3> m3{ {{ {1, 2}, {3, 4}, {5, 6} }} };
	Matrix<2, 3> m4{ {{ {1, 2}, {3, 3}, {5, 6} }} };

	ASSERT_EQ(m2, m3);
	ASSERT_EQ(m3, m2);

	ASSERT_NE(m1, m2);
	ASSERT_NE(m2, m4);
	ASSERT_NE(m3, m4);
	ASSERT_NE(m4, m1);
}

TEST(Matrix, addition)
{
	Matrix<2, 3> m1;
	Matrix<2, 3> m2{ {{ {1, 2}, {2, 3}, {3, 4} }} };
	Matrix<2, 3> m3{ {{ {1, 2}, {2, 3}, {3, 4} }} };
	Matrix<2, 3> m4{ {{ {1, 2}, {2, 1}, {2, 2} }} };
	Matrix<2, 3> m5{ {{ {2, 4}, {4, 4}, {5, 6} }} };

	ASSERT_EQ(m2 + m1, m2);
	ASSERT_EQ(m1 + m3, m2);
	ASSERT_EQ(m2 + m4, m5);
	ASSERT_EQ(m3 + m4, m5);
	ASSERT_EQ(m2 + m4, m3 + m4);
	ASSERT_EQ(m2 + m4 + m1, m3 + m4);
}

TEST(Matrix, substraction)
{
	Matrix<2, 3> m1;
	Matrix<2, 3> m2{ {{ {1, 2}, {2, 3}, {3, 4} }} };
	Matrix<2, 3> m3{ {{ {1, 2}, {2, 3}, {3, 4} }} };
	Matrix<2, 3> m4{ {{ {1, 2}, {2, 1}, {2, 2} }} };

	Matrix<2, 3> m5{ {{ {0, 0}, {0, 2}, {1, 2} }} };
	Matrix<2, 3> m6{ {{ {0, 0}, {0, -2}, {-1, -2} }} };

	ASSERT_EQ(m2 - m1, m2);
	ASSERT_EQ(m2 - m3, m1);
	ASSERT_EQ(m2 - m4, m5);
	ASSERT_EQ(m4 - m3, m6);
	ASSERT_EQ(m2 - m4, m3 - m4);
	ASSERT_EQ(m2 - m4 - m1, m3 - m4);
}

TEST(Matrix, multiplication)
{
	Matrix<2, 3> m1{ {{ {1, 2}, {3, 4}, {5, 6} }} };
	Matrix<3, 2> m2{ {{ {1, 2, 3}, {4, 5, 6} }} };
	Matrix<3, 3> m3{ {{ {9, 12, 15}, {19, 26, 33}, {29, 40, 51} }} };
	Matrix<2, 2> m4{ {{ {22, 28}, {49, 64} }} };

	ASSERT_EQ(m1 * m2, m3);
	ASSERT_EQ(m2 * m1, m4);
}

TEST(Matrix, scalar_multiplication)
{
	Matrix<2, 3> m1;
	Matrix<2, 3> m2{ {{ {1, 2}, {2, 3}, {3, 4} }} };
	Matrix<2, 3> m3{ {{ {2, 4}, {4, 6}, {6, 8} }} };

	ASSERT_EQ(3 * m1, m1);
	ASSERT_EQ(2 * m2, m3);
	ASSERT_EQ(2u * m2, m3);
}

TEST(Matrix, read_value)
{
	Matrix<2, 3> m{ {{ {1, 2}, {3, 4}, {5, 6} }} };

	ASSERT_EQ(m(0, 0), 1);
	ASSERT_EQ(m(1, 0), 2);
	ASSERT_EQ(m(0, 1), 3);
	ASSERT_EQ(m(1, 1), 4);
	ASSERT_EQ(m(0, 2), 5);
	ASSERT_EQ(m(1, 2), 6);
}

TEST(Matrix, write_value)
{
	Matrix<2, 3> m{ {{ {1, 2}, {3, 4}, {5, 6} }} };
	m(0, 0) = 0;
	m(1, 1) = 9;
	m(0, 2) = 7;

	ASSERT_EQ(m(0, 0), 0);
	ASSERT_EQ(m(1, 0), 2);
	ASSERT_EQ(m(0, 1), 3);
	ASSERT_EQ(m(1, 1), 9);
	ASSERT_EQ(m(0, 2), 7);
	ASSERT_EQ(m(1, 2), 6);
}

TEST(Matrix, transpose)
{
	Matrix<2, 3> m1{ {{ {1, 2}, {3, 4}, {5, 6} }} };
	Matrix<3, 2> m2{ {{ {1, 3, 5}, {2, 4, 6} }} };

	ASSERT_EQ(m1.transpose(), m2);
	ASSERT_EQ(m2.transpose(), m1);
}

TEST(Matrix, multiplication_of_transpose)
{
	Matrix<3, 2> m1{ {{ {1, 2, 3}, {4, 5, 6} }} };
	Matrix<1, 3> m2{ {{ {1}, {2}, {3} }} };
	Matrix<1, 2> m3{ {{ {14}, {32} }} };

	ASSERT_EQ(m1 * m2, m3);
	ASSERT_EQ(m2.transpose() * m1.transpose(), m3.transpose());
}

TEST(Matrix, multiply)
{
	Matrix<3, 2> m1{ {{ {1, 2, 3}, {4, 5, 6} }} };
	Matrix<3, 2> m2{ {{ {2, 3, 4}, {5, 6, 7} }} };
	Matrix<3, 2> m3{ {{ {2, 6, 12}, {20, 30, 42} }} };

	ASSERT_EQ(multiply(m1, m2), m3);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
