#pragma once

#include "matrices/matrices.h"

#include <tuple>

namespace {

template<size_t A, size_t B, size_t... Args>
struct Weights
{
	using type = decltype(std::tuple_cat(std::tuple<Matrix<B, A, double>>{}, typename Weights<B, Args...>::type{}));
};

template<size_t A, size_t B>
struct Weights<A, B>
{
	using type = std::tuple<Matrix<B, A, double>>;
};

template<size_t A, size_t... Args>
struct InAndOut
{
	using Input = std::array<double, A>;
	using Output = typename InAndOut<Args...>::Output;
};

template<size_t A>
struct InAndOut<A>
{
	using Output = std::array<double, A>;
};

} // namespace

struct Identity
{
	static constexpr double f(double x) {
		return x;
	}

	static constexpr double fp(double) {
		return 1;
	}
};

template<size_t... Args>
struct Topology
{
	using NeuronLayers = std::tuple<Matrix<Args, 1, double>...>;
	using WeightLayers = typename Weights<Args...>::type;
	using Input = typename InAndOut<Args...>::Input;
	using Output = typename InAndOut<Args...>::Output;
};

template<typename InnerTopology, typename Activation>
class Network
{
public:
	using NeuronLayers = typename InnerTopology::NeuronLayers;
	using WeightLayers = typename InnerTopology::WeightLayers;
	using Input = typename InnerTopology::Input;
	using Output = typename InnerTopology::Output;

	constexpr Network()
	{
	}

	constexpr Network(WeightLayers&& l, double rate)
		: m_learningRate{rate}
		, m_weightLayers{l}
	{
	}

	constexpr void forward(Input in)
	{
		for (size_t i=0; i<in.size(); ++i) {
			std::get<0>(m_neuronLayers)(i, 0) = in[i];
		}
		forward(std::make_index_sequence<std::tuple_size<WeightLayers>::value>{});
	}

	constexpr void backpropagate(Output output)
	{
		auto tmp = std::remove_reference_t<decltype(std::get<IndexOfLastLayer>(m_neuronLayers))>{ {{ output }} };
		std::get<IndexOfLastLayer>(m_errorLayers) = tmp - std::get<IndexOfLastLayer>(m_neuronLayers);
		backpropagate(std::make_index_sequence<std::tuple_size<WeightLayers>::value>{});
	}

	constexpr Output output() const
	{
		Output out{0};
		for (size_t i=0; i<out.size(); ++i) {
			out[i] = std::get<IndexOfLastLayer>(m_neuronLayers)(i, 0);
		}
		return out;
	}

	constexpr double error(Output expected) const
	{
		auto out = output();
		double err = 0;
		for (size_t i=0; i<expected.size(); ++i) {
			auto e = out[i] - expected[i];
			err += e * e / 2;
		}
		return err;
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
		std::get<I+1>(m_aggregatedLayers) = std::get<I>(m_neuronLayers) * std::get<I>(m_weightLayers);
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
		auto delta = m_learningRate * std::get<I>(m_neuronLayers).transpose() * error;

		std::get<I>(m_errorLayers) = error * std::get<I>(m_weightLayers).transpose();
		std::get<I>(m_weightLayers) += delta;
	}

	constexpr static size_t IndexOfLastLayer = std::tuple_size<NeuronLayers>::value - 1;
	const double m_learningRate;

	NeuronLayers m_neuronLayers;
	NeuronLayers m_aggregatedLayers;
	NeuronLayers m_errorLayers;
	WeightLayers m_weightLayers;
};
