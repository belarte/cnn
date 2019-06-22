#pragma once

#include "math/random.h"

#include <array>
#include <string>
#include <iostream>
#include <sstream>

template<size_t Columns, size_t Rows, typename Type = int,
	typename std::enable_if_t<(Columns > 0), size_t> = 0,
	typename std::enable_if_t<(Rows > 0), size_t> = 0>
class Matrix
{
public:
	constexpr Matrix() : m_data {0} {
	}

	constexpr Matrix(RandomGenerator<Type> gen)
	{
		for (size_t j=0; j<Rows; ++j) {
			for (size_t i=0; i<Columns; ++i) {
				m_data[j][i] = gen.yield();
			}
		}
	}

	constexpr Matrix(const std::array<std::array<Type, Columns>, Rows>& data) :
		m_data{data}
	{}

	constexpr bool operator==(const Matrix<Columns, Rows, Type>& other) const {
		return m_data == other.m_data;
	}

	const Type& operator()(size_t i, size_t j) const
	{
		return m_data.at(j).at(i);
	}

	Type& operator()(size_t i, size_t j)
	{
		return m_data.at(j).at(i);
	}

	constexpr auto& operator+=(const Matrix<Columns, Rows, Type>& other) {
		for (size_t j=0; j<Rows; ++j) {
			for (size_t i=0; i<Columns; ++i) {
				m_data[j][i] += other.m_data[j][i];
			}
		}
		return *this;
	}

	constexpr auto& operator-=(const Matrix<Columns, Rows, Type>& other) {
		for (size_t j=0; j<Rows; ++j) {
			for (size_t i=0; i<Columns; ++i) {
				m_data[j][i] -= other.m_data[j][i];
			}
		}
		return *this;
	}

	constexpr auto transpose() const
	{
		std::array<std::array<Type, Rows>, Columns> result{0};
		for (size_t j=0; j<Rows; ++j) {
			for (size_t i=0; i<Columns; ++i) {
				result[i][j] = m_data[j][i];
			}
		}
		return Matrix<Rows, Columns, Type>{result};
	}

	std::string to_string() const {
		std::ostringstream oss;

		for (size_t j=0; j<Rows; ++j) {
			oss << "[ ";
			for (size_t i=0; i<Columns; ++i) {
				oss << m_data[j][i] << ' ';
			}
			oss << "]\n";
		}

		return oss.str();
	}

	template<typename Fun>
	constexpr void apply(Fun&& f)
	{
		for (size_t j=0; j<Rows; ++j) {
			for (size_t i=0; i<Columns; ++i) {
				m_data[j][i] = f(m_data[j][i]);
			}
		}
	}

private:
	template<size_t C, size_t R, typename T1, typename T2>
	friend constexpr auto operator*(T2 value, const Matrix<C, R, T1>& right);

	template<size_t D1, size_t D2, size_t D3, typename T>
	friend constexpr auto operator*(Matrix<D1, D2, T> left, const Matrix<D3, D1, T>& right);

	// similar to numpy multiply
	template<size_t C, size_t R, typename T>
	friend constexpr auto multiply(const Matrix<C, R, T> &left, const Matrix<C, R, T> &righ);

	std::array<std::array<Type, Columns>, Rows> m_data;
};

template<size_t S, typename T>
constexpr std::ostream& operator<<(std::ostream& os, const std::array<T, S>& a)
{
	os << "[ ";
	for (size_t i=0; i<a.size(); ++i) {
		os << a[i] << ", ";
	}
	os << "]";
   return os;
}

template<size_t C, size_t R, typename T>
constexpr std::ostream& operator<<(std::ostream& os, const Matrix<C, R, T>& m)
{
   os << m.to_string();
   return os;
}

template<size_t C, size_t R, typename T>
constexpr bool operator!=(const Matrix<C, R, T>& left, const Matrix<C, R, T>& right)
{
	return ! (left == right);
}

template<size_t C, size_t R, typename T>
constexpr auto operator+(Matrix<C, R, T> left, const Matrix<C, R, T>& right)
{
	return left += right;
}

template<size_t C, size_t R, typename T>
constexpr auto operator-(Matrix<C, R, T> left, const Matrix<C, R, T>& right)
{
	return left -= right;
}

template<size_t D1, size_t D2, size_t D3, typename T>
constexpr auto operator*(Matrix<D1, D2, T> left, const Matrix<D3, D1, T>& right)
{
	Matrix<D3, D2, T> result;
	for (size_t j=0; j<D2; ++j) {
		for (size_t i=0; i<D3; ++i) {
			for (size_t k=0; k<D1; ++k) {
				result.m_data[j][i] += left.m_data[j][k] * right.m_data[k][i];
			}
		}
	}
	return result;
}

template<size_t C, size_t R, typename T1, typename T2>
constexpr auto operator*(T2 value, const Matrix<C, R, T1>& right)
{
	Matrix<C, R, T1> result;
	for (size_t j=0; j<R; ++j) {
		for (size_t i=0; i<C; ++i) {
			result.m_data[j][i] = value * right.m_data[j][i];
		}
	}
	return result;
}

template<size_t C, size_t R, typename T>
constexpr auto multiply(const Matrix<C, R, T> &left, const Matrix<C, R, T> &right)
{
	Matrix<C, R, T> result;
	for (size_t j=0; j<R; ++j) {
		for (size_t i=0; i<C; ++i) {
			result.m_data[j][i] = left.m_data[j][i] * right.m_data[j][i];
		}
	}
	return result;
}
