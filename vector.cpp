#include "vector.h"

typedef linear::vector vector;

vector::vector(size_t count) {
	for (size_t i = 0; i < count; ++i) {
		data.push_back(0);
	}
}

vector::vector(size_t count, long double value) {
	for (size_t i = 0; i < count; ++i) {
		data.push_back(value);
	}
}

vector::vector(const std::initializer_list<long double>& list) {
	std::cout << list.size() << std::endl;
	for (auto& it : list) {
		data.push_back(it);
	}
}

vector& vector::operator=(const std::initializer_list<long double>& list) {
	if (list.size() != list.size()) {
		data.clear();
	}

	for (auto& it : list) {
		data.push_back(it);
	}
	return *this;
}

size_t vector::size() const noexcept {
	return data.size();
}

std::vector<long double> vector::get_data() const noexcept {
	return data;
}

long double& vector::operator[](const size_t i) {
	return data[i];
}

const long double& vector::operator[](const size_t i) const {
	return data[i];
}

void vector::push_back(const long double value, const size_t count){
	for (size_t i = 0; i < count; ++i) {
		data.push_back(value);
	}
}

std::ostream& linear::operator<<(std::ostream& out, const vector& vec) {
	std::cout << '(';
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if ((i + 1) != vec.size()) {
			std::cout << ", ";
		}
	}
	std::cout << ')';
	return out;
}

vector& vector::operator+=(const vector& rhs) {
	if (data.size() != rhs.data.size())
		throw std::invalid_argument("Error: different dimensions!");
	for (size_t i = 0; i < data.size(); ++i) {
		data[i] += rhs.data[i];
	}
	return *this;
}

vector& vector::operator-=(const vector& rhs) {
	if (data.size() != rhs.data.size())
		throw std::invalid_argument("Error: different dimensions!");
	for (size_t i = 0; i < data.size(); ++i) {
		data[i] -= rhs.data[i];
	}
	return *this;
}


vector& vector::operator*=(const long double rhs) {
	for (size_t i = 0; i < data.size(); ++i) {
		data[i] *= rhs;
	}
	return *this;
}

vector& vector::operator/=(const long double rhs) {
	for (size_t i = 0; i < data.size(); ++i) {
		data[i] /= rhs;
	}
	return *this;
}

long double linear::scalar(const vector& lhs, const vector& rhs) {
	if (lhs.size() != rhs.size())
		throw std::invalid_argument("Error: different dimensions!");
	long double result = 0;
	for (size_t i = 0; i < lhs.size(); ++i) {
		result += lhs[i] * rhs[i];
	}
	return result;
}

vector linear::operator+(const vector& lhs, const vector& rhs) {
	vector result(lhs);
	result += rhs;
	return result;
}

vector linear::operator-(const vector& lhs, const vector& rhs) {
	vector result(lhs);
	result -= rhs;
	return result;
}

vector linear::operator*(const vector& lhs, const long double rhs) {
	vector result(lhs);
	result *= rhs;
	return result;
}

vector linear::operator*(const long double lhs, const vector& rhs) {
	vector result(rhs);
	result *= lhs;
	return result;
}


vector linear::operator/(const vector& lhs, const long double rhs) {
	vector result(lhs);
	result /= rhs;
	return result;
}

vector linear::operator/(const long double lhs, const vector& rhs) {
	vector result(rhs);
	result /= lhs;
	return result;
}

[[nodiscard]] bool linear::operator==(const vector& lhs, const vector& rhs) {
	return lhs.get_data() == rhs.get_data();
}

[[nodiscard]] bool linear::operator!=(const vector& lhs, const vector& rhs) {
	return !(lhs == rhs);
}