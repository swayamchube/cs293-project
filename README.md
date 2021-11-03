# Mandelbrot Zoom (200050141)

I am hoping that I would be able to do this project using the SFML library with its bindings in C++. The header file `Mandelbrot.h` already contains all the required helper code. The only thing left to do is to shade the entire region using the function `double isBounded(Complex)`.
The main idea is to take the `double` (which is between 0 and 1) that is returned by the function to determine the color of that particular pixel, which is called the naive escape-time algorithm (I shall implement this in the latter half of this project). The time complexity is rather large for something like this so I expect a good 5 mins of runtime.

For compilation you may need to install the `libsfml-dev` package using your distro's package manager and make the build directory (`mkdir build`). Then simply run the `Makefile` and the executable would be placed in the `./build` directory. (You really don't need the `s++` compiler for this)

**NOTE:** If you're using a tiling window manager like DWM, change from tiling mode to floating mode (the window could be ill-formed otherwise).
