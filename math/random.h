#pragma once

#include <random>

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
	std::uniform_int_distribution<T> m_distribution;
};
