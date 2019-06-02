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

int main(int, char**)
{
	std::cout << "Start testing..." << std::endl;

	forward_no_hidden_layer();
	forward_two_hidden_layers();

	std::cout << "Done!" << std::endl;
	return 0;
}
