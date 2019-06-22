#pragma once

#include <random>

namespace {

template<typename T, class Enable = void>
struct Distribution{};

template<typename T>
struct Distribution<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
	using type = std::uniform_int_distribution<T>;
};

template<typename T>
struct Distribution<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
	using type = std::uniform_real_distribution<T>;
};

}

template<typename T>
class RandomGenerator
{
public:
	RandomGenerator(T min, T max)
		: m_engine{ std::random_device{}() }
		, m_distribution{ min, max }
	{}

	T yield()
	{
		return m_distribution(m_engine);
	}

private:
	std::mt19937_64 m_engine;
	typename Distribution<T>::type m_distribution;
};
