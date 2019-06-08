#include "network.h"
#include "test/assert.h"

void forward_no_hidden_layer()
{
	using Net = Network<Topology<3, 2>, Identity>;

	Matrix<2, 3, double> m{ {{ {1, 4}, {2, 5}, {3, 6} }} };
	auto n = Net{std::make_tuple(m), 1};

	n.forward({3, 2, 1});

	Net::Output output{10, 28};
	ASSERT_EQ(n.output(), output);
}

void forward_two_hidden_layers()
{
	using Net = Network<Topology<3, 2, 5, 1>, Identity>;

	Matrix<2, 3, double> l1{ {{ {1, 4}, {2, 5}, {3, 6} }} };
	Matrix<5, 2, double> l2{ {{ {1, 0, 3, 0, 5}, {0, 2, 0, 4, 0} }} };
	Matrix<1, 5, double> l3{ {{ {5}, {4}, {3}, {2}, {1} }} };
	auto n = Net{std::make_tuple(l1, l2, l3), 1};

	n.forward({3, 2, 1});

	Net::Output output{638};
	ASSERT_EQ(n.output(), output);
}

void error_is_null_when_output_equals_expected()
{
	using Net = Network<Topology<3, 2>, Identity>;
	Matrix<2, 3, double> m{ {{ {1, 4}, {2, 5}, {3, 6} }} };
	auto n = Net{std::make_tuple(m), 1};

	n.forward({3, 2, 1});

	Net::Output expected{10, 28};
	ASSERT_EQ(n.error(expected), 0);
}

void error_is_positive_when_output_differs_from_expected()
{
	using Net = Network<Topology<3, 2>, Identity>;

	Matrix<2, 3, double> m{ {{ {1, 4}, {2, 5}, {3, 6} }} };
	auto n = Net{std::make_tuple(m), 1};

	n.forward({3, 2, 1});

	Net::Output expected{8, 32};
	ASSERT_EQ(n.error(expected), 10);
}

void backpropagation_corrects_weights()
{
	using Net = Network<Topology<3, 4, 2>, Identity>;

	Matrix<4, 3, double> l1{ {{ {1, 3, 1, 6}, {2, 1, 5, 1}, {1, 4, 1, 7} }} };
	Matrix<2, 4, double> l2{ {{ {0, 1}, {1, 2}, {2, 0}, {0, 1} }} };
	auto n = Net{ std::make_tuple(l1, l2), 0.5 };

	std::array<double, 3> input{1, 0, 1};
	Net::Output trainingOutput{0, 30};
	Net::Output expectedOutput{-779, 80};

	n.forward(input);
	n.backpropagate(trainingOutput);
	n.forward(input);
	ASSERT_EQ(n.output(), expectedOutput);
}

int main(int, char**)
{
	std::cout << "Start testing..." << std::endl;

	try {
		forward_no_hidden_layer();
		forward_two_hidden_layers();
		error_is_null_when_output_equals_expected();
		error_is_positive_when_output_differs_from_expected();
		backpropagation_corrects_weights();
	} catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	std::cout << "Done!" << std::endl;
	return 0;
}
