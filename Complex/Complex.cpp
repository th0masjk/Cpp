#include "Complex.h"

#include <cmath>

constexpr int sgn(double n) { return (n < 0 ? -1 : (n == 0 ? 0 : 1)); }

//
// Field definitions
//

const Complex Complex::I(0.0, 1.0);


//
// Constructors
//
Complex::Complex() { Real = Imaginary = 0.0; }

Complex::Complex(const Complex& z) {
	Real = z.Real;
	Imaginary = z.Imaginary;
}

Complex::Complex(double real) {
	Real = real;
	Imaginary = 0.0;
}

Complex::Complex(double real, double imaginary) {
	Real = real;
	Imaginary = imaginary;
}


//
// Methods
//

double Complex::Abs() {
	return sqrt(Real * Real + Imaginary * Imaginary);
}

double Complex::Arg() {
	return atan2(Imaginary, Real);
}


//
// Static methods
//

Complex Complex::Exp(Complex z) {
	Complex w(exp(z.Real) * cos(z.Imaginary), exp(z.Real) * sin(z.Imaginary));
	return w;
}

Complex Complex::Log(Complex z) {
	Complex w(log(z.Real * z.Real + z.Imaginary * z.Imaginary) / 2.0, atan2(z.Imaginary, z.Real));
	return w;
}

Complex Complex::Pow(Complex z)
{
	Complex w(
		pow(Real * Real + Imaginary * Imaginary, z.Real / 2.0) * exp(-z.Imaginary * Arg()) * cos(z.Real * Arg() + 0.5 * z.Imaginary * log(Real * Real + Imaginary * Imaginary)),
		pow(Real * Real + Imaginary * Imaginary, z.Real / 2.0) * exp(-z.Imaginary * Arg()) * sin(z.Real * Arg() + 0.5 * z.Imaginary * log(Real * Real + Imaginary * Imaginary)));
	return w;
}

Complex Complex::Sqrt()
{
	// sqrt(a+b*i):
	//   a = sqrt((re + sqrt(re^2 + im^2)) / 2)
	//   b = sgn(im)sqrt((-re + sqrt(re^2 + im^2)) / 2)
	struct Complex w;

	Complex z(
		sqrt((Real + sqrt(Real * Real + Imaginary * Imaginary)) / 2.0),
		sgn(Imaginary) * sqrt((-Real + sqrt(Real * Real + Imaginary * Imaginary)) / 2.0)
	);
	return z;
}


//
// Operators
//

Complex Complex::operator +(const Complex& z)
{
	Complex w(Real + z.Real, Imaginary + z.Imaginary);
	return w;
}

Complex Complex::operator -(const Complex& z)
{
	Complex w(Real - z.Real, Imaginary - z.Imaginary);
	return w;
}

Complex Complex::operator *(const Complex& z)
{
	Complex w(
		Real * z.Real - Imaginary * z.Imaginary,
		Real * z.Imaginary + Real * z.Imaginary + Imaginary * z.Real);
	return w;
}

Complex Complex::operator /(const Complex& z)
{
	/*
		(a+bi)/(c+di) = (ac+bd)/(c^2+d^2, (bc-ad)//c^2+d^2)
	*/

	auto a = Real;
	auto b = Imaginary;
	auto c = z.Real;
	auto d = z.Imaginary;

	Complex w(
		(a*c + b*d) / (c*c + d*d),
		(b*c - a*d) / (c*c + d*d));
	return w;
}

Complex::operator double()
{
	return Abs();
}