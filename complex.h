#pragma once
#include <iostream>
namespace linear {
	class complex {
	public:
		complex() = default;
		complex(long  double, long double);
		complex(const complex&);
		complex(complex&&) noexcept;
		complex& operator=(const complex&) noexcept;
		complex& operator=(complex&&) noexcept;
		complex& operator+=(const complex&);
		complex& operator+=(const long double);
		complex& operator-=(const complex&);
		complex& operator-=(const long double);
		complex& operator*=(const complex&);
		complex& operator*=(const long double);
		complex& operator/=(const complex&);
		complex& operator/=(const long double);

		void real(const long double);
		void imag(const long double);

		inline long double real() const;
		inline long double imag() const;


	private:
		long double re = 0.l;
		long double im = 0.l;
	};
	std::ostream& operator<<(std::ostream& out, const complex& matrix);

	complex operator+(const complex&, const complex&);
	complex operator+(const complex&, const long double);
	complex operator+(const long double, const complex&);

	complex operator-(const complex&, const complex&);
	complex operator-(const complex&, const long double);
	complex operator-(const long double, const complex&);

	complex operator*(const complex&, const complex&);
	complex operator*(const complex&, const long double);
	complex operator*(const long double, const complex&);

	complex operator/(const complex&, const complex&);
	complex operator/(const complex&, const long double);
	complex operator/(const long double, const complex&);

	complex operator""_i(unsigned long long);
	complex operator""_i(long double);

	inline bool operator==(const complex&, const complex&);
	inline bool operator==(const long double, const complex&);
	inline bool operator==(const complex&, const long double);
	inline bool operator!=(const complex&, const complex&);
	inline bool operator!=(const long double, const complex&);
	inline bool operator!=(const complex&, const long double);

	long double abs(const complex&);
	long double arg(const complex&);
	complex exp(const complex&);
	complex log(const complex&);
	complex pow(const complex&, const complex&);
	complex pow(const complex&, const long double);
	complex pow(const long double, const complex&);
	complex sqrt(const complex&);
	complex conj(const complex&);
}