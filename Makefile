.PHONY: run, clean
project: src/main.o src/Mandelbrot.o
	g++ src/main.o src/Mandelbrot.o -o build/project -L./lib -lsprite -lGL -lGLEW -lglfw -lSOIL -lGLC -I./include

main.o: src/main.cpp
	g++ -c src/main.cpp -o src/main.o

Mandelbrot.o: src/Mandelbrot.h Mandelbrot.cpp 
	g++ -c src/Mandelbrot.cpp -o src/Mandelbrot.o

clean:
	rm src/*.o

run:
	build/project
