#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SFML/Graphics.hpp>
#include "Mandelbrot.h"

class Application {
public:
	// Constructors
	Application();

	// Destructor 
	~Application();

	// Member Functions
	void run();
private:
	sf::RenderWindow* m_window;
	std::string m_name;
	int m_size;
	Complex m_origin;
	double m_zoom; // lies between 0 and 1. Closer to 0, faster the zoom
};

#endif

/*
SAMPLE OF main.cpp

int main() {
	Application application(800, 800, "Mandelbrot");
	Application.run();
}
*/
