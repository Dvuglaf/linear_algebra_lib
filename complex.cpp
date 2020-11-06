#include "complex.h"
#include <iostream>
#include <cmath>

typedef linear::complex complex;

complex::complex() :re(0), im(0) { ; }

complex::complex(long double real, long double imaginary) :re(real), im(imaginary) { ; }

complex::complex(const complex& rhs) : re(rhs.re), im(rhs.im) { ; }

complex::complex(complex&& rhs) noexcept : re(rhs.re), im(rhs.im) { ; }

complex& complex::operator=(const complex& rhs) noexcept {
	re = rhs.re;
	im = rhs.im;
	return *this;
}

complex& complex::operator=(complex&& rhs) noexcept {
	re = rhs.re;
	im = rhs.im;
	return *this;
}

void complex::real(const long double value) {
	re = value;
}

void complex::imag(const long double value) {
	im = value;
}

inline long double complex::real() const {
	return re;
}

inline long double complex::imag() const {
	return im;
}

std::ostream& linear::operator<<(std::ostream& out, const complex& complex) {
	out << '(' << complex.real()<< ", " << complex.imag() << ')' << std::endl;
	return out;
}

complex linear::operator+(const complex& lhs, const complex& rhs) {
	complex result(lhs);
	result += rhs;
	return result;
}

complex linear::operator+(const complex& lhs, const long double value) {
	return complex(lhs) += value;
}

complex linear::operator+(const long double value, const complex& rhs) {
	return complex(rhs) += value;
}

complex linear::operator-(const complex& lhs, const complex& rhs) {
	complex result(lhs);
	result -= rhs;
	return result;
}

complex linear::operator-(const complex& lhs, const long double value) {
	return complex(lhs) -= value;
}

complex linear::operator-(const long double value, const complex& rhs) {
	return complex(rhs) -= value;
}

complex linear::operator*(const complex& lhs, const complex& rhs) {
	complex temp(lhs);
	temp *= rhs;
	return temp;
}

complex linear::operator*(const complex& lhs, const long double rhs) {
	complex temp(lhs);
	temp *= rhs;
	return temp;
}

complex linear::operator*(const long double lhs, const complex& rhs) {
	complex temp(rhs);
	temp *= lhs;
	return temp;
}

complex linear::operator/(const complex& lhs, const complex& rhs) {
	complex temp(lhs);
	temp /= rhs;
	return temp;
}

complex linear::operator/(const complex& lhs, const long double rhs) {
	complex temp(lhs);
	temp /= rhs;
	return temp;
}

complex linear::operator/(const long double lhs, const complex& rhs) {
	complex temp(rhs);
	temp /= lhs;
	return temp;
}

complex linear::operator""_i(unsigned long long imaginary){
	return complex(0, static_cast<long double>(imaginary));
}

complex linear::operator""_i(long double imaginary) {
	return complex(0, imaginary);
}

inline complex& complex::operator+=(const complex& rhs) {
	re += rhs.re;
	im += rhs.im;
	return *this;
}

inline complex& complex::operator+=(const long double value) {
	re += value;
	return *this;
}

inline complex& complex::operator-=(const complex& rhs) {
	re -= rhs.re;
	im -= rhs.im;
	return *this;
}

inline complex& complex::operator-=(const long double value) {
	re -= value;
	return *this;
}

complex& complex::operator*=(const complex& rhs) {
	auto new_real = re * rhs.re - im * rhs.im;
	im = re * rhs.im + rhs.re*im;
	re = new_real;
	return *this;
}

complex& complex::operator*=(const long double rhs) {
	re *= rhs;
	im *= rhs;
	return *this;
}

complex& complex::operator/=(const complex& rhs) {
	auto new_real = (re * rhs.re + im * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
	im = (im * rhs.re - re * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
	re = new_real;
	return *this;
	
}

complex& complex::operator/=(const long double rhs) {
	re /= rhs;
	im /= rhs;
	return *this;
}

inline bool linear::operator==(const complex& lhs, const complex& rhs) {
	return (lhs.real() == rhs.real() && lhs.imag() == rhs.imag()) ? true : false;
}

inline bool linear::operator==(const long double lhs, const complex& rhs) {
	return (lhs == rhs.real() && rhs.imag() == 0) ? true : false;
}

inline bool linear::operator==(const complex& lhs, const long double rhs) {
	return (lhs.real() == rhs && lhs.imag() == 0) ? true : false;
}

inline bool linear::operator!=(const complex& lhs, const complex& rhs) {
	return !(lhs == rhs);
}

inline bool linear::operator!=(const long double lhs, const complex& rhs) {
	return !(lhs == rhs);
}

inline bool linear::operator!=(const complex& lhs, const long double rhs) {
	return !(lhs == rhs);
}

long double linear::abs(const complex& z) {
	return std::sqrt(z.real() * z.real() + z.imag() * z.imag());
}

long double linear::arg(const complex& z) {
	return std::atan2l(z.imag(), z.real());
}

complex linear::exp(const complex& z) {
	return complex(std::exp(z.real()) * cos(z.imag()), std::exp(z.real())*sin(z.imag()));
}

complex linear::log(const complex& z) {
	return complex(std::log(linear::abs(z)), linear::arg(z));
}

complex linear::pow(const complex& lhs, const complex& rhs) {
	return complex(linear::exp(rhs * linear::log(lhs)));
}

complex linear::pow(const complex& lhs, const long double rhs) {
	return complex(linear::exp(rhs * linear::log(lhs)));
}

complex linear::pow(const long double lhs, const complex& rhs) {
	return complex(linear::exp(rhs * std::log(lhs)));
}

complex linear::sqrt(const complex& z) {
	return pow(z, 0.5);
}

complex linear::conj(const complex& z) {
	return complex(z.real(), -z.imag());
}

