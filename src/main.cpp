#include <cstdio>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "Mandelbrot.h"

#define ORIGIN_X 300
#define ORIGIN_Y 300
#define WINDOW_X 600
#define WINDOW_Y 600
#define EULER_CONSTANT 2.718281828459045

/*
 -2                   800 px                   +2
 +----------------------------------------------+ +2
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 | 800 px                0                      | 0
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 +----------------------------------------------+ -2
*/

/*
 * 1. Use a simple black-white shading.
 * 2. Iterate over all the pixels in the image.
 */

enum ERRORS {
	NONE, LOG
};

int main(int argc, char* argv[]) {
	std::FILE* logfile = fopen("mandelbrot.log", "w");

	if (logfile == nullptr) {
		fprintf(stderr, "Unable to open log file. Exiting");
		exit(ERRORS::LOG);
	}

	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Mandelbrot");
	fprintf(logfile, "Window Opened!\n");

	sf::Image image;
	image.create(WINDOW_X, WINDOW_Y);

	sf::Texture texture;

	sf::Sprite sprite;

	double x_max = 2.0;
	double y_max = 2.0;

	double zoom_inverse = 1;

	Complex origin(-1.3, 0);

	while(window.isOpen()) {
		sf::Event event;

		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				fprintf(logfile, "Window Closed!\n");
				window.close();
			}
		}

		window.clear();
		// Naive Escape time algorithm
		for (int i = 0; i < WINDOW_X; ++i) {
			for (int j = 0; j < WINDOW_Y; ++j) {
				// Find scaled coordinates
				double x, y; 
				x = static_cast<double>(i - ORIGIN_X)/ORIGIN_X * x_max;
				y = static_cast<double>(j - ORIGIN_Y)/ORIGIN_Y * y_max;
				Complex pixel(x, y);
				pixel = pixel + origin;
				double fraction = isBounded(pixel);
				unsigned short rgb = 255 * fraction;
				image.setPixel(i, j, sf::Color(rgb, rgb, rgb));
			}
		}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		window.draw(sprite);
		window.display();

		x_max *= zoom_inverse;
		y_max *= zoom_inverse;
	}
}
