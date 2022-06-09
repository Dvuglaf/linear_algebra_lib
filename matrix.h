#pragma once
#include <vector>
#include <iostream>
#include <exception>
#include "vector.h"
namespace linear {

	class matrix {
	public:
		matrix(size_t, size_t, long double = 0.l);

		inline long double& operator()(size_t, size_t);
		inline const long double& operator()(size_t, size_t) const;

		size_t rows() const noexcept;
		size_t columns() const noexcept;
		std::vector<long double> get_row(size_t) const noexcept;
		size_t size() const noexcept;

		matrix& operator+=(const matrix&);
		matrix& operator-=(const matrix&);

		matrix& operator*=(long double);
		matrix& operator/=(long double);


		void add_row(long double value);
		void add_row(const vector&);
		void add_column(long double value);


	private:

		std::vector< std::vector<long double> > data;
		size_t n;
		size_t m;


	};
	matrix transpose(const matrix&);
	matrix transpose(const linear::vector&);

	std::ostream& operator<<(std::ostream&, const matrix&);

	matrix operator+(const matrix&, const matrix&);

	matrix operator-(const matrix&, const matrix&);

	matrix operator*(const matrix&, long double);
	matrix operator*(long double, const matrix&);
	matrix operator*(const matrix&, const matrix&);
	matrix operator*(const matrix&, const vector&);
	matrix operator*(const vector&, const matrix&);

	matrix operator/(const matrix&, long double);

	[[nodiscard]] bool operator==(const matrix&, const matrix&);
	[[nodiscard]] bool operator!=(const matrix&, const matrix&);

	[[nodiscard]] bool is_zero(const matrix&);
	[[nodiscard]] bool is_identity(const matrix&);
	[[nodiscard]] bool is_square(const matrix&);
	[[nodiscard]] bool is_symmetric(const matrix&);
	[[nodiscard]] bool is_colon(const matrix&);
	[[nodiscard]] bool is_row(const matrix&);
}
