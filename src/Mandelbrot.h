#include <cmath>
#include "../include/simplecpp"

class Complex {
public:
	Complex();
	Complex(double, double);
	Complex(const Complex&);
	Complex(const simplecpp::Rectangle&);

	double getX();
	double getY();

	double getLength();

	Complex operator=(const Complex&);
	Complex operator+(const Complex&);
	Complex operator*(const Complex&);
private:
	double x, y;
};

bool isBounded(Complex);
