#include "network.h"

#include "gtest/gtest.h"

using Identity = function::Identity;

TEST(Network, forward_no_hidden_layer)
{
	using Net = Network<Topology<3, 2>, Identity>;

	Matrix<2, 3, double> m{ {{ {1, 4}, {2, 5}, {3, 6} }} };
	auto n = Net{std::make_tuple(m), {}, {}};

	n.forward({3, 2, 1});

	Net::Output output{10, 28};
	ASSERT_EQ(n.output(), output);
}

TEST(Network, forward_two_hidden_layers)
{
	using Net = Network<Topology<3, 2, 5, 1>, Identity>;

	Matrix<2, 3, double> l1{ {{ {1, 4}, {2, 5}, {3, 6} }} };
	Matrix<5, 2, double> l2{ {{ {1, 0, 3, 0, 5}, {0, 2, 0, 4, 0} }} };
	Matrix<1, 5, double> l3{ {{ {5}, {4}, {3}, {2}, {1} }} };
	auto n = Net{std::make_tuple(l1, l2, l3), {}, {}};

	n.forward({3, 2, 1});

	Net::Output output{638};
	ASSERT_EQ(n.output(), output);
}

TEST(Network, error_is_null_when_output_equals_expected)
{
	using Net = Network<Topology<3, 2>, Identity>;
	Matrix<2, 3, double> m{ {{ {1, 4}, {2, 5}, {3, 6} }} };
	auto n = Net{std::make_tuple(m), {}, {}};

	n.forward({3, 2, 1});

	Net::Output expected{10, 28};
	ASSERT_EQ(n.error(expected), 0);
}

TEST(Network, error_is_positive_when_output_differs_from_expected)
{
	using Net = Network<Topology<3, 2>, Identity>;

	Matrix<2, 3, double> m{ {{ {1, 4}, {2, 5}, {3, 6} }} };
	auto n = Net{std::make_tuple(m), {}, {}};

	n.forward({3, 2, 1});

	Net::Output expected{8, 32};
	ASSERT_EQ(n.error(expected), 10);
}

TEST(Network, backpropagation_corrects_weights_and_biases)
{
	using Net = Network<Topology<3, 4, 2>, Identity>;

	Matrix<4, 3, double> l1{ {{ {1, 3, 1, 6}, {2, 1, 5, 1}, {1, 4, 1, 7} }} };
	Matrix<2, 4, double> l2{ {{ {0, 1}, {1, 2}, {2, 0}, {0, 1} }} };
	auto n = Net{ std::make_tuple(l1, l2), {}, Net::Parameters{ 0.5 } };

	std::array<double, 3> input{1, 0, 1};
	Net::Output trainingOutput{0, 30};
	Net::Output expectedOutput{-558, 49.5};

	n.forward(input);
	n.backpropagate(trainingOutput);
	n.forward(input);
	ASSERT_EQ(n.output(), expectedOutput);
}

TEST(Network, bias)
{
	using Net = Network<Topology<2, 3, 1>, Identity>;

	Matrix<3, 2, double> l1;
	Matrix<1, 3, double> l2{ {{ {1}, {1}, {1} }} };
	Matrix<3, 1, double> b1{ {{ {1, 3, 5} }} };
	Matrix<1, 1, double> b2{ {{ {2} }} };
	auto n = Net{ std::make_tuple(l1, l2), std::make_tuple(b1, b2), {} };
	Net::Input input{ 1, 1 };
	Net::Output expected { 11 };

	n.forward(input);

	ASSERT_EQ(expected, n.output());
}

TEST(Network, random_init)
{
	using Net = Network<Topology<2, 3, 1>, Identity>;

	RandomGenerator gen(1.0, 2.0);
	auto n = Net{ gen, {} };
	Net::Input in{ 1, 1 };
	Net::Output out{ 0 };

	n.forward(in);
	auto error = n.error(out);
	ASSERT_NE(0, error);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
