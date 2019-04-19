#include <array>
#include <iostream>
#include <sstream>

template<size_t Columns, size_t Rows>
class Matrix
{
public:
	Matrix() : m_data {0} {
	}

	Matrix(const std::array<std::array<int, Columns>, Rows>& data) :
		m_data{data}
	{}

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
	std::array<std::array<int, Columns>, Rows> m_data;
};


template<size_t Columns, size_t Rows>
std::ostream& operator<<(std::ostream& os, const Matrix<Columns, Rows>& m)
{
   os << m.to_string();
   return os;
}
