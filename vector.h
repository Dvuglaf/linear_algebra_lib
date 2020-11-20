#pragma once

#include <iostream>
#include <vector>
namespace linear {
	class vector {
	public:
		vector(size_t);
		vector(size_t, long double);
		vector(const std::initializer_list<long double>&);
		vector& operator=(const std::initializer_list<long double>&);
		size_t size() const noexcept;
		std::vector <long double> get_data() const noexcept;
		long double& operator[](const size_t);
		const long double& operator[](const size_t) const;
		void push_back(const long double value, const size_t = 1);
		vector& operator+=(const vector&);
		vector& operator-=(const vector&);
		vector& operator*=(const long double);
		vector& operator/=(const long double);

		long double scalar(const vector&);



	public:
		std::vector<long double> data;
	};

	std::ostream& operator<<(std::ostream&, const vector&);

	vector operator+(const vector&, const vector&);

	vector operator-(const vector&, const vector&);
	
	vector operator*(const vector&, const long double);
	vector operator*(const long double, const vector&);

	vector operator/(const vector&, const long double);
	vector operator/(const long double, const vector&);

	[[nodiscard]] bool operator==(const vector&, const vector&);
	[[nodiscard]] bool operator!=(const vector&, const vector&);

	long double scalar(const vector&, const vector&);



}