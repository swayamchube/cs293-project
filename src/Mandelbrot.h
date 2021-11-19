#ifndef __MANDELBROT_H__
#define __MANDELBROT_H__

/**
 * Simple Complex number class
 * Provides a subset of the facilities provided by
 * the std::complex class
 */
class Complex {
public:
	/* Constructors */
	Complex();
	Complex(double, double);
	Complex(const Complex&);

	/* Getters */
	double getX();
	double getY();

	double getLength(); // returns modulus of the complex number 

	/* Operator Overloads */
	// Arithmetic Operators
	Complex operator=(const Complex&);
	Complex operator+(const Complex&);
	Complex operator*(const Complex&);

	Complex& operator+=(const Complex&);
	Complex& operator-=(const Complex&);
	Complex& operator*=(const Complex&);
	
	// Logical Operators
	bool operator==(const Complex&);
	bool operator!=(const Complex&);
private:
	double x, y; // x + iy
};

/* Helper Function */
double isBounded(Complex, int);

#endif //__MANDELBROT_H__
