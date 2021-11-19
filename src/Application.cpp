#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <thread>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "Application.h"
#include "Timer.h"
#include "Vector.h"

// The number of iterations we begin with
#define ITERATIONS_INIT 50

/**
 * This constructor takes in:
 * 1. Name of the window
 * 2. Size of the window (it will be a square window)
 * 3. Inverse of the zoom (the amount to zoom per render)
 * 4. The point of zoom
 * 5. Name of the log file (in case of unrecoverable errors)
 */
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

// TODO: Multithread run (use 4 threads, hardcode this)
/**
 * This does almost all the heavy lifting
 * 1. First it checks whether the the context window is properly formed
 *
 * 2. Checks whether the log file is streamed
 *
 * 3. Three components, an Image, Texture and Sprite are defined
 *    These are used to draw the mandelbrot set on the window.
 *    The image is loaded into the texture which is then loaded 
 *    into the sprite which is finally drawn on screen.
 * 
 * 4. At the same time we also check for events like:
 *    Closing the window: Gracefully exit from this
 *    Clicking the spacebar to pause
 *    Increasing or decreasing the zoom rate with f and s respectively
 *
 * 5. Note that after every zoom, the iterations are changed for the next
 *    in order to maintain a level of detail.
 *    Ofcourse there is a cap on the maximum number of iterations, given by 200.
 *    The larger this value, the more detail one would have but that comes at 
 *    the cost of a significant drop in FPS
 * 
 * 6. The algoithm used to draw the set is the Naive Escape Time algorithm
 *    This iterates over each pixel and finds the fraction of iterations 
 *    required for the complex number represented by that pixel to become 
 *    unbounded. This fraction is then used to shade the pixel (RGB)
 *
 * 6. This also makes sure that the frame rate does not drop below 1, which is
 *    facilitated by the use of a the timer class defined in src/Timer.h
 */
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
				//unsigned short rgb = 255 * fraction;

				int r = bounded.r * fraction + unbounded.r * (1 - fraction);
				int b = bounded.b * fraction + unbounded.b * (1 - fraction);
				int g = bounded.g * fraction + unbounded.g * (1 - fraction);

				image.setPixel(i, j, sf::Color(r, g, b));
			}
		}

		texture.loadFromImage(image);
		sprite.setTexture(texture);

		m_window->draw(sprite);
		m_window->display();

		long long duration = timer.getTimeElapsed();

		fprintf(m_logFile, "duration = %lld microseconds\n", duration);

		// TODO: Come up with a good bound for FPS (1 sec is too low)
		if (duration > 1e6) { // if FPS drops below 1 
			mx_max = 2;
			my_max = 2;
			iterations = ITERATIONS_INIT; // Un-Hardcode this
			continue;
		}

		mx_max *= m_zoom;
		my_max *= m_zoom;

		// TODO: Come up with a better increment to (int)iterations
		iterations /= m_zoom;
		
		if (iterations > ITER_MAX)
			iterations = ITER_MAX;

		fprintf(m_logFile, "iterations = %d\n", iterations);

		fprintf(m_logFile, "--------------------------\n");
	}
}

// Private Member Functions

// may close the window
/**
 * 1. This first pauses the zoom
 * 2. Then, starts a timer on 2 seconds for you to reselect the 
 *    zoom point (done through the updateOrigin() function)
 * 3. After those two seconds, if the spacebar is pressed, then it unpauses
 */
void Application::toggleZoom() {
	std::cerr << "Zoom has been paused!" << std::endl;
	m_paused = true;
	old_zoom = m_zoom; // stores the zoom
	m_zoom = 1; // resets the zoom

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
/**
 * This polls the mouse. Once the click position is obtained, 
 * the m_origin variable is changed suitably.
 * **This function may also close the window**
 */
void Application::updateOrigin() {
	/**
	 * Wait 2 seconds for the user to reselect the origin. 
	 * If no action takes place, break out of the loop
	 */
	Timer timer;
	bool updated = false;

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
					
				updated = true;
				break;
			}
		}
	}
	if (updated)
		std::cerr << "Origin Updated" << std::endl;
}

// This resets the application to its original state
void Application::reset() {
	mx_max = 2.0;
	my_max = 2.0;
	m_zoom = 0.95; // TODO: Figure out a way to un-hardcode this
	std::cerr << "Reset" << std::endl;
}

// This makes the zoom faster
void Application::incrementZoom() {
	m_zoom -= 0.01;
	std::cerr << "Incremented Zoom" << std::endl;
}

// This makes the zoom slower
void Application::decrementZoom() {
	m_zoom += 0.01;
	std::cerr << "Decremented Zoom" << std::endl;
}

//More detailes are provided with the implementation
int getClickedSprite(Vector<sf::Sprite>& Sprites, sf::Vector2i position);

/**
 * The following is a naive way to implement a splash screen
 * The user is given an option to choose the colorscheme for 
 * the mandelbrot set.
 *
 * The options are rendered as 3 different sprites
 * It would have been better to define a Button class and 
 * let the user click on it with animations but I didn't have 
 * enough time to implement it with such a level of abstraction
 */
void Application::splash() {
	// std::cout << "Splash Screen" << std::endl;
	
	Vector<sf::Image> Images(3);
	Vector<sf::Sprite> Sprites(3);
	Vector<sf::Texture> Textures(3);

	//sf::Texture texture;
	//sf::Sprite sprite;

	sf::Text text;
	sf::Font font;

	if (!font.loadFromFile("fonts/JetBrainsMono-Bold.ttf")) {
		std::cerr << "Failure to load font! Exiting..." << std::endl;
		exit(1);
	}

	text.setFont(font);

	text.setString("Choose a Colorscheme");

	text.setFillColor(sf::Color::White);

	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	sf::FloatRect value = text.getLocalBounds();

	text.setPosition((WINDOW_SIZE - value.width)/2.0f, 0);


	// Create Image Sizes
	Images[0].create(150, 150);
	Images[1].create(150, 150);
	Images[2].create(150, 150);

	// Set up the position of sprites
	Sprites[0].setPosition(0, 100);
	Sprites[1].setPosition(225, 100);
	Sprites[2].setPosition(450, 100);


	// Shade the rectangle(s)
	shadeImageLeftToRight(Images[0], sf::Color(255,0,0), sf::Color(0,0,0));
	shadeImageLeftToRight(Images[1], sf::Color(0,0,255), sf::Color(0,0,0));
	shadeImageLeftToRight(Images[2], sf::Color(255,0,0), sf::Color(0,0,255));


	// Load and Set Textures
	Textures[0].loadFromImage(Images[0]);
	Sprites[0].setTexture(Textures[0]);

	Textures[1].loadFromImage(Images[1]);
	Sprites[1].setTexture(Textures[1]);

	Textures[2].loadFromImage(Images[2]);
	Sprites[2].setTexture(Textures[2]);

	// Has the user chosen the scheme?
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

				switch(getClickedSprite(Sprites, position)) {
					case 0:
						bounded = sf::Color(0, 0, 0);
						unbounded = sf::Color(255, 0, 0);
						chosen = true;
						break;
					case 1:
						bounded = sf::Color(0, 0, 0);
						unbounded = sf::Color(0, 0, 255);
						chosen = true;
						break;
					case 2:
						bounded = sf::Color(0, 0, 255);
						unbounded = sf::Color(255, 0, 0);
						chosen = true;
						break;
					default:
						break;
				}
			}
		}

		m_window->draw(Sprites[0]);
		m_window->draw(Sprites[1]);
		m_window->draw(Sprites[2]);

		m_window->draw(text);

		m_window->display();
	}
	// TODO: If you have time, implement a continue button
}


///////////////////////////////////////////////////////////////////////////
// Additional Non-Class Function(s);

/**
 * This function shades a rectangle which is represented by an image 
 * from left to right given the color to the left and the color to the right
 * I decided against using things like frag-shaders since this can be done 
 * by simply accessing each pixel on the image without a significant delay
 */
void shadeImageLeftToRight(sf::Image& image, sf::Color left, sf::Color right) {
	sf::Vector2u img_size = image.getSize();

	int length = img_size.x;
	int height = img_size.y;

	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < height; ++j) {
			// computes the RGB for each pixel
			// A linear descent in each is assumed from left to right
			uint32_t r = ((length - i) * left.r + i * right.r)/length;
			uint32_t g = ((length - i) * left.g + i * right.g)/length;
			uint32_t b = ((length - i) * left.b + i * right.b)/length;

			image.setPixel(i, j, sf::Color(r, g, b));
		}
	}
}

/**
 * This is used to check whether the mouse click was on one of the sprrites
 * If it was the function returns the index of the corresponding sprite
 * If not it returns -1
 */
int getClickedSprite(Vector<sf::Sprite>& Sprites, sf::Vector2i position) {
	
	for (int i = 0; i < Sprites.size(); ++i) {
		// x and y coordinates of the click
		int x = position.x;
		int y = position.y;

		// size of the sprite
		sf::FloatRect bounds = Sprites[i].getLocalBounds();
		int height = bounds.height;
		int width = bounds.width;

		// the top left corner of the sprite
		sf::Vector2f top = Sprites[i].getPosition();

		if (x > top.x && x < top.x + width && y > top.y && y < top.y + height) {
			return i;
		}
	}

	return -1;
}
