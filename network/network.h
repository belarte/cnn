#pragma once

#include "math/functions.h"
#include "matrices/matrices.h"

#include <tuple>

namespace {

template<size_t A, size_t B, size_t... Args>
struct Weights
{
	using matrix_type = Matrix<B, A, double>;
	using type = decltype(std::tuple_cat(std::tuple<matrix_type>{}, Weights<B, Args...>::value));

	Weights()
		: value{ std::tuple_cat(std::make_tuple(matrix_type{}, Weights<B, Args...>{})) }
	{}

	Weights(RandomGenerator<double>& gen)
		: value{ std::tuple_cat(std::make_tuple(matrix_type{ gen }), Weights<B, Args...>{ gen }.value) }
	{}

	type value;
};

template<size_t A, size_t B>
struct Weights<A, B>
{
	using matrix_type = Matrix<B, A, double>;
	using type = std::tuple<matrix_type>;

	Weights() {}

	Weights(RandomGenerator<double>& gen)
		: value{ std::make_tuple(matrix_type{ gen }) }
	{}

	type value;
};

template<size_t A, size_t... Args>
struct Biases
{
	using type = std::tuple<Matrix<Args, 1, double>...>;

	Biases() {}

	Biases(RandomGenerator<double> gen)
		: value{ std::make_tuple(Matrix<Args, 1, double>{ gen }...) }
	{}

	type value;
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

template<size_t... Args>
struct Topology
{
	using NeuronLayers = std::tuple<Matrix<Args, 1, double>...>;
	using WeightLayers = typename Weights<Args...>::type;
	using BiasLayers = typename Biases<Args...>::type;
	using Input = typename InAndOut<Args...>::Input;
	using Output = typename InAndOut<Args...>::Output;

	using WeightsGen = Weights<Args...>;
	using BiasesGen = Biases<Args...>;
};

template<typename InnerTopology, typename Activation>
class Network
{
public:
	using NeuronLayers = typename InnerTopology::NeuronLayers;
	using WeightLayers = typename InnerTopology::WeightLayers;
	using BiasLayers = typename InnerTopology::BiasLayers;
	using Input = typename InnerTopology::Input;
	using Output = typename InnerTopology::Output;

	struct Parameters
	{
		const double LearningRate;
		const double TargetError;
		const uint32_t MaxEpoch;
	};

	struct Sample
	{
		Input input;
		Output output;
	};

	using TrainingSample = std::vector<Sample>;

	Network(RandomGenerator<double> gen, Parameters params)
		: m_params{ params }
		, m_weightLayers{ typename InnerTopology::WeightsGen{ gen }.value }
		, m_biasLayers{ typename InnerTopology::BiasesGen{ gen }.value }
	{
	}

	constexpr Network(WeightLayers&& l, BiasLayers&& b, Parameters params)
		: m_params{ params }
		, m_weightLayers{ l }
		, m_biasLayers{ b }
	{
	}

	void train(const TrainingSample& samples)
	{
		double err = std::numeric_limits<double>::max();
		uint32_t iter = 0;

		while (iter < m_params.MaxEpoch && err > m_params.TargetError) {
			err = 0;

			for (const auto& sample : samples) {
				forward(sample.input);
				err += error(sample.output);
				backpropagate(sample.output);
			}
			++iter;
			if (iter % 100 == 0) std::cout << "#" << iter << " error=" << err << std::endl;
		}
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
		std::get<I+1>(m_aggregatedLayers) = std::get<I>(m_neuronLayers) * std::get<I>(m_weightLayers) + std::get<I>(m_biasLayers);
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
		auto delta = m_params.LearningRate * std::get<I>(m_neuronLayers).transpose() * error;

		std::get<I>(m_errorLayers) = error * std::get<I>(m_weightLayers).transpose();
		std::get<I>(m_weightLayers) += delta;
		std::get<I>(m_biasLayers) += m_params.LearningRate * error;
	}

	constexpr static size_t IndexOfLastLayer = std::tuple_size<NeuronLayers>::value - 1;
	const Parameters m_params;

	NeuronLayers m_neuronLayers;
	NeuronLayers m_aggregatedLayers;
	NeuronLayers m_errorLayers;
	WeightLayers m_weightLayers;
	BiasLayers m_biasLayers;
};
