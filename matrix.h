#pragma once
#include <vector>
#include <iostream>
#include <exception>
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

		matrix& operator*=(long double);

		void add_row(long double value);
		void add_column(long double value);


	private:

		std::vector< std::vector<long double> > data;
		size_t n;
		size_t m;


	};
	matrix transpose(const matrix&);

	std::ostream& operator<<(std::ostream&, const matrix&);
	matrix operator*(const matrix&, const matrix&);
	matrix operator+(const matrix&, const matrix&);

	bool operator==(const matrix&, const matrix&);
	bool operator!=(const matrix&, const matrix&);

	bool is_zero(const matrix&);
	bool is_identity(const matrix&);
	bool is_square(const matrix&);
	bool is_symmetric(const matrix&);
}