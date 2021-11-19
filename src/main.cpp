#include <iostream>
#include <cstdio>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "Mandelbrot.h"
#include "Application.h"

constexpr double EULER_CONSTANT = 2.718281828459045;

/*
 -2                   600 px                   +2
 +----------------------------------------------+ +2
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 | 600 px                0                      | 600 px
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 |                                              |
 +----------------------------------------------+ -2
                      600 px
*/

/*
 * If you would like to make changes to the main.cpp file,
 * the call for constructing the application is:
 * Application(NAME_OF_WINDOW, SIZE_OF_WINDOW, INVERSE_OF_ZOOM, POINT_OF_ZOOM, NAME_OF_LOG_FILE)
 */

enum ERRORS {
	NONE, LOG
};

int main(int argc, char** argv) {
	Complex origin(-1.4, 0);

	// Checks for command line arguments
	if (argc != 1) {
		if (argc == 3) {
			double x = std::stod(argv[1]);
			double y = std::stod(argv[2]);
			origin = Complex(x, y);
		}
		else {
			std::cerr << "error: invalid number of arguments" << std::endl;
			std::cerr << "usages: \n\t(1) build/project <x_coordinate> <y_coordinate> \n\t(2) build/project" << std::endl;
			exit(1);
		}
	}
	// spawn application
	Application application("Mandelbrot", 600, 0.95, origin, "mandelbrot.log");
	
	// splash screen
	application.splash();

	// run the application
	application.run();
}
