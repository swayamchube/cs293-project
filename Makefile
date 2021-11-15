.PHONY: run, clean
project: src/main.o src/Mandelbrot.o src/Application.o
	g++ src/main.o src/Mandelbrot.o src/Application.o -o build/project -L./lib -lsprite -lGL -lGLEW -lglfw -lSOIL -lGLC -lsfml-graphics -lsfml-window -lsfml-system -I./include 

main.o: src/main.cpp
	g++ -c src/main.cpp -o src/main.o

Mandelbrot.o: src/Mandelbrot.h Mandelbrot.cpp 
	g++ -c src/Mandelbrot.cpp -o src/Mandelbrot.o

Application.o: src/Application.h src/Application.cpp
	g++ -c src/Application.cpp -o src/Application.o

clean:
	rm src/*.o

run:
	build/project
