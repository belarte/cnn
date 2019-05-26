#include "network.h"

int main(int, char**)
{
	std::cout << "Start testing..." << std::endl;

	Network<2, 5, 3> n;

	Matrix<3 ,2> m{ {{ {1, 2, 3}, {4, 5, 6} }} };
	auto n1 = Network<3, 2>{std::make_tuple(m)};

	std::cout << "Done!" << std::endl;
	return 0;
}
