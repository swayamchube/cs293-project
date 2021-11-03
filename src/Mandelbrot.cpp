#include "Mandelbrot.h"
#include <cmath>

Complex::Complex() : x(0), y(0) { }
Complex::Complex(double x, double y) : x(x), y(y) { }
Complex::Complex(const Complex& other) : x(other.x), y(other.y) { }

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

// The most important function in this project
bool isBounded(Complex val, Complex c) {
	for (int _ = 0; _ < 50; ++_) {
		if (val.getLength() > 2) {
			return false;
		}
		val = val * val + c;
	}
	return true;
}
