#include "matrix.h"

typedef linear::matrix matrix;

std::ostream& linear::operator<<(std::ostream& out, const matrix& matrix) {
	for (size_t i = 0; i < matrix.rows(); ++i) {
		for (size_t j = 0; j < matrix.columns(); ++j) {
			std::cout << matrix(i, j) << ' ';
		}
		std::cout << std::endl;
	}
	return out;
}

matrix linear::operator+(const matrix& lhs, const matrix& rhs) {
	matrix result(lhs);
	result += rhs;
	return result;
}



matrix::matrix(const size_t rows, const size_t columns, const long double value) {
	n = rows;
	m = columns;
	for (size_t i = 0; i < rows; ++i)
		data.push_back(std::vector<long double>(columns, value));

}

inline long double& matrix::operator()(const size_t i, const size_t j) {
	if (i >= n || j >= m) {
		throw std::out_of_range("Error: out of range");
	}
	return data[i][j];
}

inline const long double& matrix::operator()(const size_t i, const size_t j) const {
	if (i >= n || j >= m) {
		throw std::out_of_range("Error: out of range");
	}
	return data[i][j];
}

size_t matrix::rows() const noexcept {
	return n;
}

size_t matrix::columns() const noexcept {
	return m;
}

 std::vector<long double> matrix::get_row(size_t row) const noexcept {
	return data[row];
}

 size_t matrix::size() const noexcept {
	return n * m;
}

matrix& matrix::operator+=(const matrix& rhs) {
	if (n != rhs.rows() || m != rhs.columns()) {
		throw std::invalid_argument("Different dimensions of matrix");
	}
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			(*this)(i, j) += rhs(i, j);
		}
	}
	return *this;
}

matrix& matrix::operator-=(const matrix& rhs) {
	if (n != rhs.rows() || m != rhs.columns()) {
		throw std::invalid_argument("Different dimensions of matrix");
	}
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			(*this)(i, j) -= rhs(i, j);
		}
	}
	return *this;
}


matrix& matrix::operator*=(const long double value) {
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			(*this)(i, j) *= value;
		}
	}
	return *this;
}

matrix& matrix::operator/=(const long double value) {
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			(*this)(i, j) /= value;
		}
	}
	return *this;
}

matrix linear::operator-(const matrix& lhs, const matrix& rhs) {
	matrix temp(lhs);
	temp -= rhs;
	return temp;
}

matrix linear::operator*(const matrix& lhs, const long double rhs) {
	matrix temp(lhs);
	temp *= rhs;
	return temp;
}

matrix linear::operator*(const long double lhs, const matrix& rhs) {
	matrix temp(rhs);
	temp *= lhs;
	return temp;
}

matrix linear::operator*(const matrix& lhs, const matrix& rhs) {
	
	if (lhs.columns() != rhs.rows()) {
		throw std::invalid_argument("Error: number of columns first matrix and number of rows second matrix are different!");
	}
	matrix result(lhs.rows(), rhs.columns());
	for (size_t i = 0; i < lhs.rows(); ++i) {
		for (size_t j = 0; j < rhs.columns(); ++j) {
			for (size_t k = 0; k < lhs.columns(); ++k) {
				result(i, j) += lhs(i, k) * rhs(k, j);
			}
		}
	}
	return result;
}

matrix linear::operator*(const matrix& lhs, const vector& rhs){
	if (!is_colon(lhs)) {
		throw std::invalid_argument("Error: first argument must be colon vector!");
	}
	matrix result(lhs.rows(), rhs.size());
	for (size_t i = 0; i < lhs.columns(); ++i) {
		for (size_t j = 0; j < rhs.size(); ++j) {
			for (size_t k = 0; k < lhs.columns(); ++k) {
				result(i, j) += lhs(i, k) * rhs[k];
			}
		}
	}
	return result;
}

matrix linear::operator*(const vector& lhs, const matrix& rhs) {
	if (lhs.size() != rhs.rows()) {
		throw std::invalid_argument("Error: first argument must be colon vector!");
	}
	matrix result(lhs.size(), rhs.columns());
	for (size_t i = 0; i < lhs.size(); ++i) {
		for (size_t j = 0; j < rhs.columns(); ++j) {
			for (size_t k = 0; k < lhs.size(); ++k) {
				result(i, j) += lhs[k] * rhs(k, j);
			}
		}
	}
	return result;
}

matrix linear::operator/(const matrix& lhs, const long double rhs) {
	matrix temp(lhs);
	temp /= rhs;
	return temp;

}

matrix linear::transpose(const matrix& mat) {
	matrix temp(mat.columns(), mat.rows());
	for (size_t i = 0; i < mat.rows(); ++i) {
		for (size_t j = 0; j < mat.columns(); ++j) {
			temp(j, i) = mat(i, j);
		}
	}
	return temp;
}

matrix linear::transpose(const vector& vec) {
	matrix temp(vec.size(), 1);
	for (size_t i = 0; i < vec.size(); ++i) {
		temp(i, 1) = vec[i];
	}
	return temp;
}

void matrix::add_row(const long double value) {
	data.push_back(std::vector<long double>(m, value));
	++n;
}

void matrix::add_row(const vector& vector) {
	data.push_back(vector.get_data());
	++n;
}

void matrix::add_column(const long double value) {
	for (auto& it : data) {
		it.push_back(value);
	}
	++m;
}

bool linear::is_zero(const matrix& matrix) {
	for (size_t i = 0; i < matrix.rows(); ++i) {
		for (size_t j = 0; j < matrix.columns(); ++j) {
			if (matrix(i, j) != 0)
				return false;
		}
	}
	return true;
}

[[nodiscard]] bool linear::is_identity(const matrix& matrix) {
	for (size_t i = 0; i < matrix.rows(); ++i) {
		for (size_t j = 0; j < matrix.columns(); ++j) {
			if (i == j) {
				if (matrix(i, j) == 1)
					continue;
				else
					return false;
			}
			else {
				if (matrix(i, j) != 0)
					return false;
			}
		}
	}
	return true;
}

[[nodiscard]] bool linear::is_square(const matrix& matrix) {
	return matrix.columns() == matrix.rows();
}

[[nodiscard]] bool linear::is_symmetric(const matrix& matrix) {
	return matrix == transpose(matrix);
}

[[nodiscard]] bool linear::is_colon(const matrix& matrix) {
	return matrix.columns() == 1;
}

[[nodiscard]] bool linear::is_row(const matrix& matrix) {
	return matrix.rows() == 1;
}


[[nodiscard]] bool linear::operator==(const matrix& lhs, const matrix& rhs) {
	if (lhs.rows() != rhs.rows() || lhs.columns() != rhs.columns())
		return false;

	for (size_t i = 0; i < lhs.rows(); ++i) {
		if (lhs.get_row(i) != rhs.get_row(i))
			return false;
	}
	return true;
}

[[nodiscard]] bool linear::operator!=(const matrix& lhs, const matrix& rhs) {
	return !(lhs == rhs);
}

