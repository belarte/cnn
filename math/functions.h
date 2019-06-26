#pragma once

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

}
