#pragma once

#include <cmath>

namespace function {

struct Identity
{
	static constexpr double f(double x) {
		return x;
	}

	static constexpr double fp(double) {
		return 1;
	}
};

struct Logistic
{
	static double f(double x) {
		return 1.0 / (1 + std::exp(-x));
	}

	static double fp(double x) {
		return f(x) * (1 - f(x));
	}
};

}
