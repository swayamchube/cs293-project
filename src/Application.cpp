#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "Application.h"
#include "Timer.h"

#define ITERATIONS_INIT 50

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
	this->bounded = sf::Color(0,0,0);
	this->unbounded = sf::Color(255,0,0);

	//fprintf(m_logFile, "Application has been constructed\n");
}

Application::~Application() {
	//fprintf(m_logFile, "Application has ended\n");
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

// TODO: Multithread run (use 4 threads, hardcode this)

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

	const int ORIGIN_X = WINDOW_SIZE/2;
	const int ORIGIN_Y = WINDOW_SIZE/2;

	int iterations = ITERATIONS_INIT;

	m_window->setFramerateLimit(30);
	m_window->setVerticalSyncEnabled(true);

	while(m_window->isOpen()) {
		sf::Event event;

		while(m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window->close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					// pause
					toggleZoom();
				}
				else if (event.key.code == sf::Keyboard::R) {
					// reset 
					reset();
				}
				else if (event.key.code == sf::Keyboard::F) {
					// faster
					incrementZoom();
				}
				else if (event.key.code == sf::Keyboard::S) {
					// slower
					decrementZoom();
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				std::cerr << "Origin Reselection is possible only after pausing" << std::endl;
			}
		}

		if (!m_window->isOpen()) {
			break;
		}

		m_window->clear();

		Timer timer;

		// Naive Escape time algorithm
		for (int i = 0; i < WINDOW_SIZE; ++i) {
			for (int j = 0; j < WINDOW_SIZE; ++j) {
				// Find scaled coordinates
				double x, y; 
				x = static_cast<double>(i - ORIGIN_X)/ORIGIN_X * mx_max;
				y = static_cast<double>(j - ORIGIN_Y)/ORIGIN_Y * my_max;
				Complex pixel(x, -y);
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

		long long duration = timer.getTimeElapsed();

		std::cout << duration << std::endl;

		// TODO: Come up with a good bound for FPS (1 sec is too low)
		if (duration > 1e6) { // if FPS drops below 1 
			mx_max = 2;
			my_max = 2;
			iterations = ITERATIONS_INIT; // Un-Hardcode this
			continue;
		}

		mx_max *= m_zoom;
		my_max *= m_zoom;

		//std::printf("mx_max = %lf, my_max = %lf\n", mx_max, my_max);
		
		// TODO: Come up with a better increment to (int)iterations
		iterations /= m_zoom;
		
		if (iterations > ITER_MAX)
			iterations = ITER_MAX;

		//fprintf(m_logFile, "iterations = %d\n", iterations);
	}
}

// Private Member Functions

// may close the window
void Application::toggleZoom() {
	std::cout << "Zoom has been paused!" << std::endl;
	m_paused = true;
	old_zoom = m_zoom;
	m_zoom = 1;

	std::cout << "You have 2 seconds to reselect the zoom-origin" << std::endl;

	// check whether the person wants to update the origin
	updateOrigin();

	// wait for the user to unpause by pressing the spacebar
	while(m_window->isOpen() && m_paused) {
		sf::Event event;
		
		while(m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window->close();
				break;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					m_zoom = old_zoom;
					m_paused = false;
					std::cout << "Zoom Unpaused" << std::endl;
					break;
				}
			}
		}
	}
}

// This is only invoked when paused is called
void Application::updateOrigin() {
	/**
	 * Wait 2 seconds for the user to reselect the origin. 
	 * If no action takes place, break out of the loop
	 */
	Timer timer;
	while(m_window->isOpen()) {
		sf::Event event;

		long long duration = timer.getTimeElapsed();

		if (duration > 2e6) {
			break;
		}

		while(m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window->close();
				break;
			}
			else if (event.type == sf::Event::MouseButtonPressed) {

				/* Position of the click as pixels */
				sf::Vector2i position = sf::Mouse::getPosition(*m_window);
				std::cout << position.x << " " << position.y << std::endl;
				// convert position into complex number
				const int ORIGIN_X = WINDOW_SIZE/2;
				const int ORIGIN_Y = WINDOW_SIZE/2;
				double x, y; 
				x = static_cast<double>(position.x - ORIGIN_X)/ORIGIN_X * mx_max;
				y = static_cast<double>(position.y - ORIGIN_Y)/ORIGIN_Y * my_max;

				std::cout << mx_max << " " << my_max << std::endl;

				Complex pixel(x, -y);
				m_origin += pixel;

				break;
			}
		}
	}

	//std::cerr << "Origin Updated" << std::endl;
}

void Application::reset() {
	mx_max = 2.0;
	my_max = 2.0;
	m_zoom = 0.95; // TODO: Figure out a way to un-hardcode this
	std::cerr << "Reset" << std::endl;
}

void Application::incrementZoom() {
	m_zoom -= 0.01;
	std::cerr << "Incremented Zoom" << std::endl;
}

void Application::decrementZoom() {
	m_zoom += 0.01;
	std::cerr << "Decremented Zoom" << std::endl;
}

// TODO: Make the splash-screen

//void shadeImageLeftToRight(sf::Image, sf::Color, sf::Color);

/**
 * The following is a naive way to implement a splash screen
 * The user is given an option to choose the colorscheme for 
 * the mandelbrot set.
 */
void Application::splash() {
	// std::cout << "Splash Screen" << std::endl;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	image.create(100, 100);

	bool chosen = false;

	while(m_window->isOpen() && !chosen) {
		sf::Event event;
		
		m_window->clear();

		while(m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window->close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position = sf::Mouse::getPosition(*m_window);
				int i = position.x;
				int j = position.y;
				std::printf("%d, %d\n", i, j);

				if (i < 100 && j < 100) {
					chosen = true;
				}
			}
		}

		// Shade the rectangle.
		shadeImageLeftToRight(image, sf::Color(255,0,0), sf::Color(0,0,255));

		texture.loadFromImage(image);
		sprite.setTexture(texture);

		m_window->draw(sprite);
		m_window->display();
	}
}


// Additional Non-Class Function(s);

void shadeImageLeftToRight(sf::Image& image, sf::Color left, sf::Color right) {
	sf::Vector2u img_size = image.getSize();

	int length = img_size.x;
	int height = img_size.y;

	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < height; ++j) {
			uint32_t r = ((length - i) * left.r + i * right.r)/length;
			uint32_t g = ((length - i) * left.g + i * right.g)/length;
			uint32_t b = ((length - i) * left.b + i * right.b)/length;
			image.setPixel(i, j, sf::Color(r, g, b));
		}
	}
}
