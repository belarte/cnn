#include <array>
#include <iostream>
#include <sstream>

template<size_t Columns, size_t Rows, typename Type = int>
class Matrix
{
public:
	Matrix() : m_data {0} {
	}

	Matrix(const std::array<std::array<Type, Columns>, Rows>& data) :
		m_data{data}
	{}

	bool operator==(const Matrix<Columns, Rows, Type>& other) const {
		return m_data == other.m_data;
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

private:
	std::array<std::array<Type, Columns>, Rows> m_data;
};


template<size_t C, size_t R, typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<C, R, T>& m)
{
   os << m.to_string();
   return os;
}

template<size_t C, size_t R, typename T>
bool operator!=(const Matrix<C, R, T>& left, const Matrix<C, R, T>& right)
{
	return ! (left == right);
}
