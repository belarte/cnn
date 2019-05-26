#include "network.h"
#include "test/assert.h"

void forward_no_hidden_layer()
{
	Matrix<3, 2, double> m{ {{ {1, 2, 3}, {4, 5, 6} }} };
	auto n = Network<3, 2>{std::make_tuple(m)};

	Matrix<1, 3, double> input{ {{ {3}, {2}, {1} }} };
	n.forward(input);

	Matrix<1, 2, double> output{ {{ {10}, {28} }} };
	ASSERT_EQ(n.output(), output);
}

int main(int, char**)
{
	std::cout << "Start testing..." << std::endl;

	forward_no_hidden_layer();

	std::cout << "Done!" << std::endl;
	return 0;
}
