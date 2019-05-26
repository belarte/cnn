#pragma once

#include "matrices/matrices.h"

#include <tuple>

template<size_t A, size_t B, size_t... Args>
struct Weights
{
	using type = decltype(std::tuple_cat(std::tuple<Matrix<A, B, double>>{}, typename Weights<B, Args...>::type{}));
};

template<size_t A, size_t B>
struct Weights<A, B>
{
	using type = std::tuple<Matrix<A, B, double>>;
};

template<size_t... Args>
class Network
{
public:
	using NeuronLayers = std::tuple<Matrix<1, Args, double>...>;
	using WeightLayers = typename Weights<Args...>::type;
	using Input = typename std::tuple_element<0, NeuronLayers>::type;
	using Output = typename std::tuple_element<std::tuple_size<NeuronLayers>::value - 1, NeuronLayers>::type;
	using Indices = std::make_index_sequence<std::tuple_size<NeuronLayers>::value>;

	constexpr Network()
	{
	}

	constexpr Network(WeightLayers&& l)
		: m_weightLayers{l}
	{
	}

	constexpr void forward(Input in)
	{
		std::get<0>(m_neuronLayers) = in;
		forward(std::make_index_sequence<std::tuple_size<WeightLayers>::value>{});
	}

	constexpr const Output& output() const
	{
		return std::get<std::tuple_size<NeuronLayers>::value - 1>(m_neuronLayers);
	}

private:
	template<size_t... Is>
	void forward(std::index_sequence<Is...>) {
		((std::get<Is+1>(m_neuronLayers) = std::get<Is>(m_weightLayers) * std::get<Is>(m_neuronLayers)), ...);
	}

	NeuronLayers m_neuronLayers;
	WeightLayers m_weightLayers;
};
