#include <cmath>

class Complex {
public:
	Complex();
	Complex(double, double);
	Complex(const Complex&);

	double getX();
	double getY();

	double getLength();

	Complex operator=(const Complex&);
	Complex operator+(const Complex&);
	Complex operator*(const Complex&);
private:
	double x, y;
};

bool isBounded(Complex, Complex);
