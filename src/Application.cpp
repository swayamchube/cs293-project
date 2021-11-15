#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <SFML/Graphics/VertexArray.hpp>
#include "Application.h"

Application::Application(
	std::string name,
	int WINDOW_SIZE,
	double zoom,
	Complex origin,
	const char* logfile
) {
	this->m_name = name;
	this->WINDOW_SIZE = WINDOW_SIZE;
	this->m_zoom = zoom;
	this->m_origin = origin;
	this->m_window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), m_name);
	this->m_logFile = fopen(logfile, "w");

	fprintf(m_logFile, "Application has been constructed\n");
}

Application::~Application() {
	fprintf(m_logFile, "Application has ended\n");
	delete m_window;
}

int Application::checkHealth() {
	if (m_logFile == nullptr) {
		return 1;
	}
	else if (m_window == nullptr) {
		return 2;
	}
	return 0;
}

void Application::run() {
	fprintf(m_logFile, "Checking health...\n");
	
	switch(checkHealth()) {
		case 0: 
			fprintf(m_logFile, "No problems detected...\n");
			break;
		case 1:
			std::cerr << "Unable to create logfile\n Exiting..." << std::endl;
			exit(1);
			break;
		case 2:
			fprintf(m_logFile, "Unable to create window\n Exiting...\n");
			break;
	}

	fprintf(m_logFile, "No problems detected...\n");
	fprintf(m_logFile, "Application has started\n");
	// ---------------------------------------------
	
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	image.create(WINDOW_SIZE, WINDOW_SIZE);

	double x_max = 2.0;
	double y_max = 2.0;

	const int ORIGIN_X = WINDOW_SIZE/2;
	const int ORIGIN_Y = WINDOW_SIZE/2;

	int iterations = 50;

	m_window->setFramerateLimit(30);
	m_window->setVerticalSyncEnabled(true);

	while(m_window->isOpen()) {
		sf::Event event;

		while(m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window->close();
			}
		}

		m_window->clear();
		// Naive Escape time algorithm
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				// Find scaled coordinates
				double x, y; 
				x = static_cast<double>(i - ORIGIN_X)/ORIGIN_X * x_max;
				y = static_cast<double>(j - ORIGIN_Y)/ORIGIN_Y * y_max;
				Complex pixel(x, y);
				pixel = pixel + m_origin;
				double fraction = isBounded(pixel, iterations);
				unsigned short rgb = 255 * fraction;
				image.setPixel(i, j, sf::Color(255 - rgb, 0, 0));
			}
		}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		m_window->draw(sprite);
		m_window->display();

		x_max *= m_zoom;
		y_max *= m_zoom;
		iterations /= m_zoom;
		
		if (iterations > ITER_MAX)
			iterations = ITER_MAX;

		fprintf(m_logFile, "iterations = %d\n", iterations);
	}
}
