#pragma once

#include "matrices/matrices.h"

#include <tuple>

namespace {

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

} // namespace

struct Identity
{
	static constexpr double f(double x) {
		return x;
	}

	static constexpr double fp(double x) {
		return 1;
	}
};

template<size_t... Args>
struct Topology
{
	using NeuronLayers = std::tuple<Matrix<1, Args, double>...>;
	using WeightLayers = typename Weights<Args...>::type;
	using Input = typename std::tuple_element<0, NeuronLayers>::type;
	using Output = typename std::tuple_element<std::tuple_size<NeuronLayers>::value - 1, NeuronLayers>::type;
};

template<typename Activation, size_t... Args>
class Network
{
public:
	using InnerTopology = Topology<Args...>;
	using NeuronLayers = typename InnerTopology::NeuronLayers;
	using WeightLayers = typename InnerTopology::WeightLayers;
	using Input = typename InnerTopology::Input;
	using Output = typename InnerTopology::Output;

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

	constexpr void backpropagate(Output output)
	{
		std::get<IndexOfLastLayer>(m_errorLayers) = output - std::get<IndexOfLastLayer>(m_neuronLayers);
		backpropagate(std::make_index_sequence<std::tuple_size<WeightLayers>::value>{});
	}

	constexpr const Output& output() const
	{
		return std::get<IndexOfLastLayer>(m_neuronLayers);
	}

	constexpr const Output error(Output expected) const
	{
		Output result = output() - expected;
		result.apply([](double x){ return x * x / 2; });
		return result;
	}

private:
	template<size_t... Is>
	void forward(std::index_sequence<Is...>)
	{
		(forwardLayer<Is>(), ...);
	}

	template<size_t I>
	void forwardLayer()
	{
		std::get<I+1>(m_aggregatedLayers) = std::get<I>(m_weightLayers) * std::get<I>(m_neuronLayers);
		std::get<I+1>(m_neuronLayers) = std::get<I+1>(m_aggregatedLayers);
		std::get<I+1>(m_neuronLayers).apply(&Activation::f);
	}

	template<size_t... Is>
	void backpropagate(std::index_sequence<Is...>)
	{
		(backpropagateLayer<std::tuple_size<WeightLayers>::value - Is - 1>(), ...);
	}

	template<size_t I>
	void backpropagateLayer()
	{
		std::get<I + 1>(m_aggregatedLayers).apply(&Activation::fp);
		auto error = multiply(std::get<I + 1>(m_errorLayers), std::get<I + 1>(m_aggregatedLayers));
		auto delta = LearningRate * error * std::get<I>(m_neuronLayers).transpose();

		std::get<I>(m_errorLayers) = std::get<I>(m_weightLayers).transpose() * error;
		std::get<I>(m_weightLayers) += delta;
	}

	constexpr static size_t IndexOfLastLayer = std::tuple_size<NeuronLayers>::value - 1;
	constexpr static double LearningRate = 0.5;

	NeuronLayers m_neuronLayers;
	NeuronLayers m_aggregatedLayers;
	NeuronLayers m_errorLayers;
	WeightLayers m_weightLayers;
};
