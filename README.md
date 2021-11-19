# Mandelbrot Zoom (200050141)

This is the finished course project for CS293, Data Structures and Algorithms Lab.

The command to run the executable is 
```bash
$ build/project <x_coordinate> <y_coordinate>
``` 
the command line arguments are optional. The default point of zoom is $$(-1.4, 0)$$.

On running the executable, it would create a 600x600 rendering window. The details of this can be found in `src/Application.cpp`

This simulates a very primitive Mandelbrot Zoom. The controls are:
- `spacebar` to pause the zoom. On doing so you have 2 seconds to change the point of zoom
- `s` to slow down the zoom and `f` to speed it up
- `r` to reset everything

The window would reset itself once the FPS falls below 1.

Try not to resize the window, that's one feature that I didn't implement.

## Compilation and Build (GNU/LINUX)
```bash
$ ./install_dependencies
```
```bash
$ git clone https://github.com/swayamchube/cs293-project
```
```bash
$ cd cs293-project
$ mkdir build
$ make # This places the executable in ./build/project
```

**NOTE:** If you are using a tiling window manager like DWM, you may want to switch to floating mode, unless you want an ill-formed window.
