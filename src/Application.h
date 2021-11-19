#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SFML/Graphics.hpp>
#include <cstdio>
#include <string>
#include <memory>
#include "Mandelbrot.h"
#include "Vector.h"

//TODO: Come up with a better estimate for ITER_MAX
#define ITER_MAX 200

void shadeImageLeftToRight(sf::Image&, sf::Color, sf::Color);

class Application {
private:
	int checkHealth();
	void toggleZoom();
	void updateOrigin();
	void reset();
	void incrementZoom();
	void decrementZoom();
public:
	// Constructors
	Application(
		std::string name,
		int WINDOW_SIZE,
		double zoom,
		Complex origin,
		const char* logfile
	);

	// Copy Constructor is not valid
	Application(const Application&) = delete;


	// Destructor 
	~Application();

	// Member Functions
	void run(); // this does all the heavy lifting

	void splash(); // Allows the user to choose the colorscheme
private:
	sf::RenderWindow* m_window; // pointer to the window
	std::string m_name; // name of the window
	int WINDOW_SIZE; // will be a square window
	double mx_max = 2.0, my_max = 2.0;
	Complex m_origin; // the point of zoom
	double m_zoom; // lies between 0 and 1. Closer to 0, faster the zoom
	double old_zoom = 1;
	bool m_paused = false;
	std::FILE* m_logFile; // to log the errors if any
	sf::Color bounded;
	sf::Color unbounded;

};

#endif

/*
SAMPLE OF main.cpp

int main() {
	Application application("Mandelbrot", 800, 0.95, Complex(.,.), "mandelbrot.log");
	application.splash();
	application.run();
}
*/
