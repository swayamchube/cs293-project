#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SFML/Graphics.hpp>
#include <cstdio>
#include <string>
#include <memory>
#include "Mandelbrot.h"

#define ITER_MAX 100

class Application {
private:
	int checkHealth();
	void foo();
public:
	// Constructors
	Application(
		std::string name,
		int WINDOW_SIZE,
		double zoom,
		Complex origin,
		const char* logfile
	);

	// Destructor 
	~Application();

	// Member Functions
	void run(); // this does all the heavy lifting
private:
	sf::RenderWindow* m_window; // pointer to the window
	std::string m_name; // name of the window
	int WINDOW_SIZE; // will be a square window
	Complex m_origin; // the point of zoom
	double m_zoom; // lies between 0 and 1. Closer to 0, faster the zoom
	std::FILE* m_logFile; // to log the errors if any

};

#endif

/*
SAMPLE OF main.cpp

int main() {
	Application("Mandelbrot", 800, 0.9, Complex(.,.), "mandelbrot.log");
	Application.run();
}
*/
