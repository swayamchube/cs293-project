#include "Mandelbrot.h"
#include "../include/simplecpp"
#include <cmath>

Complex::Complex() : x(0), y(0) { }
Complex::Complex(double x, double y) : x(x), y(y) { }
Complex::Complex(const Complex& other) : x(other.x), y(other.y) { }
Complex::Complex(const simplecpp::Rectangle& rect) : x(rect.getX()), y(rect.getY()) { }

double Complex::getX() { return x; }
double Complex::getY() { return y; }

double Complex::getLength() { return std::sqrt(x * x + y * y); }

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

// ----------------------------------------------------------

/*
 * Checks whether the complex value is bounded under the 
 * infinite iteration given by the complex number c
 *
 * In reality, we use this with a rectangle but since there 
 * is a constructor from a rectangle to a complex number,
 * it doesn't cause any issues
 */
bool isBounded(Complex val) {
	Complex z(0, 0);
	for (int _ = 0; _ < 50; ++_) {
		if (z.getLength() > 2) 
			return false;
		z = z * z + val;
	}
	return true;
}
