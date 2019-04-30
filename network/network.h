#pragma once

#include "matrices/matrices.h"

#include <tuple>

template<size_t A, size_t B, size_t... Args>
struct Weights
{
	using type = decltype(std::tuple_cat(std::tuple<Matrix<A, B>>{}, typename Weights<B, Args...>::type{}));
};

template<size_t A, size_t B>
struct Weights<A, B>
{
	using type = std::tuple<Matrix<A, B>>;
};

template<size_t... Args>
class Network
{
public:
	using NeuronLayers = std::tuple<Matrix<1, Args, double>...>;
	using WeightLayers = typename Weights<Args...>::type;

	constexpr Network()
	{
	}

private:
	NeuronLayers m_neuronLayers;
	WeightLayers m_weightLayers;
};
