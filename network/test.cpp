#include "network.h"
#include "test/assert.h"

void forward_no_hidden_layer()
{
	Matrix<3, 2, double> m{ {{ {1, 2, 3}, {4, 5, 6} }} };
	auto n = Network<Identity, 3, 2>{std::make_tuple(m)};

	Matrix<1, 3, double> input{ {{ {3}, {2}, {1} }} };
	n.forward(input);

	Matrix<1, 2, double> output{ {{ {10}, {28} }} };
	ASSERT_EQ(n.output(), output);
}

void forward_two_hidden_layers()
{
	Matrix<3, 2, double> l1{ {{ {1, 2, 3}, {4, 5, 6} }} };
	Matrix<2, 5, double> l2{ {{ {1, 0}, {0, 2}, {3, 0}, {0, 4}, {5, 0} }} };
	Matrix<5, 1, double> l3{ {{ {5, 4, 3, 2, 1} }} };
	auto n = Network<Identity, 3, 2, 5, 1>{std::make_tuple(l1, l2, l3)};

	Matrix<1, 3, double> input{ {{ {3}, {2}, {1} }} };
	n.forward(input);

	Matrix<1, 1, double> output{ {{ {638} }} };
	ASSERT_EQ(n.output(), output);
}

void error_is_null_when_output_equals_expected()
{
	Matrix<3, 2, double> m{ {{ {1, 2, 3}, {4, 5, 6} }} };
	auto n = Network<Identity, 3, 2>{std::make_tuple(m)};

	Matrix<1, 3, double> input{ {{ {3}, {2}, {1} }} };
	n.forward(input);

	Matrix<1, 2, double> expected{ {{ {10}, {28} }} };
	Matrix<1, 2, double> error{ {{ {0}, {0} }} };
	ASSERT_EQ(n.error(expected), error);
}

void error_is_positive_when_output_differs_from_expected()
{
	Matrix<3, 2, double> m{ {{ {1, 2, 3}, {4, 5, 6} }} };
	auto n = Network<Identity, 3, 2>{std::make_tuple(m)};

	Matrix<1, 3, double> input{ {{ {3}, {2}, {1} }} };
	n.forward(input);

	Matrix<1, 2, double> expected{ {{ {8}, {32} }} };
	Matrix<1, 2, double> error{ {{ {2}, {8} }} };
	ASSERT_EQ(n.error(expected), error);
}

void backpropagation_corrects_weights()
{
	Matrix<3, 4, double> l1{ {{ {1, 2, 1}, {3, 1, 4}, {1, 5, 1}, {6, 1, 7} }} };
	Matrix<4, 2, double> l2{ {{ {0, 1, 2, 0}, {1, 2, 0, 1} }} };
	auto n = Network<Identity, 3, 4, 2>{ std::make_tuple(l1, l2) };

	Matrix<1, 3, double> intput{ {{ {1}, {0}, {1} }} };
	Matrix<1, 2, double> trainingOutput{ {{ {0}, {30} }} };
	Matrix<1, 2, double> expectedOutput{ {{ {-779}, {80} }} };

	n.forward(intput);
	n.backpropagate(trainingOutput);
	n.forward(intput);
	ASSERT_EQ(n.output(), expectedOutput);
}

int main(int, char**)
{
	std::cout << "Start testing..." << std::endl;

	forward_no_hidden_layer();
	forward_two_hidden_layers();
	error_is_null_when_output_equals_expected();
	error_is_positive_when_output_differs_from_expected();
	backpropagation_corrects_weights();

	std::cout << "Done!" << std::endl;
	return 0;
}
