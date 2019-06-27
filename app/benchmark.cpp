#include "network/network.h"

int main(int, char**)
{
	using Net = Network<Topology<2, 3, 1>, function::Logistic>;
	using Samples = Net::TrainingSample;

	RandomGenerator gen(-1.0, 1.0);

	auto n = Net{ gen, Net::Parameters{ 0.1, 0.01, 10000 } };

	auto s = Samples{
		{{0, 0}, {0}},
		{{1, 0}, {1}},
		{{0, 1}, {1}},
		{{1, 1}, {0}}
	};

	n.train(s);

	for (const auto& i : s) {
		n.forward(i.input);
		std::cout << "err=" << n.error(i.output) << std::endl;
	}

	return 0;
}
