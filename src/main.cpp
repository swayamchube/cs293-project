#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "Mandelbrot.h"

#define ORIGIN_X 400
#define ORIGIN_Y 400
#define WINDOW_X 800
#define WINDOW_Y 800

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

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Mandelbrot");
	sf::Image image;
	image.create(WINDOW_X, WINDOW_Y);
	sf::Texture texture;
	sf::Sprite sprite;


	while(window.isOpen()) {
		sf::Event event;

		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		// Naive Escape time algorithm
		for (int i = 0; i < WINDOW_X; ++i) {
			for (int j = 0; j < WINDOW_Y; ++j) {
				// find scaled coordinates
				double x, y;
				x = static_cast<double>(i - ORIGIN_X)/ORIGIN_X * 2;
				y = static_cast<double>(j - ORIGIN_Y)/ORIGIN_Y * 2;
				Complex pixel(x, y);
				double fraction = isBounded(pixel);
				unsigned short rgb = 255 * fraction;
				image.setPixel(i, j, sf::Color(rgb, rgb, rgb));
			}
		}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		window.draw(sprite);
		window.display();
	}
}
