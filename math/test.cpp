#include "math/random.h"

#include "gtest/gtest.h"

TEST(RandomInt, generate_value_within_interval)
{
	int minimum = 10;
	int maximum = 20;
	RandomGenerator gen(minimum, maximum);

	for (size_t i=0; i<100; ++i) {
		auto val = gen.yield();
		ASSERT_GE(val, minimum);
		ASSERT_LE(val, maximum);
	}
}

TEST(RandomInt, visual)
{
	RandomGenerator gen(-10, 10);

	std::cout << "Generate 20 ints in interval [-10, 10]" << std::endl;
	for (size_t i=0; i<20; ++i) {
		std::cout << gen.yield() << ' ';
	}

	std::cout << std::endl;
}

TEST(RandomDouble, generate_value_within_interval)
{
	double minimum = -1.5;
	double maximum = 2.5;
	RandomGenerator gen(minimum, maximum);

	for (size_t i=0; i<100; ++i) {
		auto val = gen.yield();
		ASSERT_GE(val, minimum);
		ASSERT_LE(val, maximum);
	}
}

TEST(RandomDouble, visual)
{
	RandomGenerator gen(-1.0, 1.0);

	std::cout << "Generate 20 doubles in interval [-1.0, 1.0]" << std::endl;
	for (size_t i=0; i<20; ++i) {
		std::cout << gen.yield() << ' ';
	}

	std::cout << std::endl;
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
