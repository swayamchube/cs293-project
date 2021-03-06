#include "Mandelbrot.h"
#include <cmath>

// Constructors
Complex::Complex() : x(0), y(0) { }
Complex::Complex(double x, double y) : x(x), y(y) { }
Complex::Complex(const Complex& other) : x(other.x), y(other.y) { }

// Getters
double Complex::getX() { 
	return x; 
}
double Complex::getY() { 
	return y; 
}

// Returns the modulus of the complex number
double Complex::getLength() { 
	return std::sqrt(x * x + y * y); 
}

// Operator Overloads
Complex Complex::operator=(const Complex& other) {
	x = other.x;
	y = other.y;
	return *this;
}

Complex Complex::operator+(const Complex& other) {
	return Complex(x + other.x, y + other.y);
}

Complex Complex::operator*(const Complex& other) {
	return Complex(x * other.x - y * other.y, x * other.y + y * other.x);
}

Complex& Complex::operator+=(const Complex& other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Complex& Complex::operator-=(const Complex& other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Complex& Complex::operator*=(const Complex& other) {
	x = x * other.x - y * other.y;
	y = x * other.y + y * other.x;
	return *this;
}

/**
 * Since we're dealing with double here, it's a better metric to
 * compare the absolute value of the difference between two doubles to
 * 10^-6 to conclude whether they're equal or not
 */
bool Complex::operator==(const Complex& rhs) {
	return (std::abs(x - rhs.x) < 1e-6 && std::abs(y - rhs.y) < 1e-6);
}

bool Complex::operator!=(const Complex& rhs) {
	return !(std::abs(x - rhs.x) < 1e-6 && std::abs(y - rhs.y) < 1e-6);
}

// ----------------------------------------------------------

/*
 * Returns the fraction of iterations required to unbound the 
 * complex number `val`
 *
 * The bound used is that of 2. 
 * There is a proper proof on the internet for this bound.
 */
double isBounded(Complex val, int iterations) {
	Complex z(0, 0);
	int i = 0;

	for (; i < iterations; ++i) {
		if (z.getLength() > 2) {
			break;
		}

		z = z * z + val;
	}

	double fraction = static_cast<double>(i)/iterations;
	return fraction;
}
