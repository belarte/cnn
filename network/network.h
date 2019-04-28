#include "matrices/matrices.h"

#include <array>
#include <tuple>

template<size_t... Args>
class Network
{
public:
	using NeuronLayers = std::tuple<Matrix<1, Args, double>...>;

	constexpr Network()
	{
	}

private:
	NeuronLayers m_neuronLayers;
};
