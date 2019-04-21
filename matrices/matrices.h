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

	constexpr Matrix(const std::array<std::array<Type, Columns>, Rows>& data) :
		m_data{data}
	{}

	constexpr bool operator==(const Matrix<Columns, Rows, Type>& other) const {
		return m_data == other.m_data;
	}

	constexpr Matrix<Columns, Rows, Type>& operator+=(const Matrix<Columns, Rows, Type>& other) {
		for (size_t j=0; j<Rows; ++j) {
			for (size_t i=0; i<Columns; ++i) {
				m_data[j][i] += other.m_data[j][i];
			}
		}
		return *this;
	}

	constexpr std::string to_string() const {
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

private:
	template<size_t D1, size_t D2, size_t D3, typename T>
	friend constexpr Matrix<D3, D2, T> operator*(Matrix<D1, D2, T> left, const Matrix<D3, D1, T>& right);

	std::array<std::array<Type, Columns>, Rows> m_data;
};


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
constexpr Matrix<C, R, T> operator+(Matrix<C, R, T> left, const Matrix<C, R, T>& right)
{
	return left += right;
}

template<size_t D1, size_t D2, size_t D3, typename T>
constexpr Matrix<D3, D2, T> operator*(Matrix<D1, D2, T> left, const Matrix<D3, D1, T>& right)
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
