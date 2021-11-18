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

// ----------------------------------------------------------

/*
 * Returns the fraction of iterations required to unbound the 
 * complex number `val`
 */
double isBounded(Complex val, int iterations) {
	Complex z(0, 0);
	int i = 0;
	for (; i < iterations; ++i) {
		if (z.getLength() > 2) 
			break;
		z = z * z + val;
	}
	double fraction = static_cast<double>(i)/iterations;
	return fraction;
}
