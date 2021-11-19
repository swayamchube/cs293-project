#ifndef __MANDELBROT_H__
#define __MANDELBROT_H__

class Complex {
public:
	// Constructors
	Complex();
	Complex(double, double);
	Complex(const Complex&);

	// Getters
	double getX();
	double getY();

	double getLength();

	// Operator Overloads
	Complex operator=(const Complex&);
	Complex operator+(const Complex&);
	Complex operator*(const Complex&);

	Complex& operator+=(const Complex&);
	Complex& operator-=(const Complex&);
	Complex& operator*=(const Complex&);

	bool operator==(const Complex&);
	bool operator!=(const Complex&);
private:
	double x, y; // x + iy
};

double isBounded(Complex, int);

#endif
