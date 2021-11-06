#include <cmath>
#include "../include/simplecpp"

class Complex {
public:
	// Constructors
	Complex();
	Complex(double, double);
	Complex(const Complex&);
	Complex(const simplecpp::Rectangle&);

	// Getters
	double getX();
	double getY();

	double getLength();

	// Operator Overloads
	Complex operator=(const Complex&);
	Complex operator+(const Complex&);
	Complex operator*(const Complex&);
private:
	double x, y;
};

double isBounded(Complex);
