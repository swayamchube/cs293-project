CFLAGS=-Wall -fno-stack-protector

.PHONY: run, clean
project: src/main.o src/Mandelbrot.o src/Application.o src/Timer.o src/Vector.o
	g++ $(CFLAGS) src/main.o src/Mandelbrot.o src/Vector.o src/Application.o src/Timer.o -o build/project -lGL -lGLEW -lglfw -lSOIL -lGLC -lsfml-graphics -lsfml-window -lsfml-system

main.o: src/main.cpp
	g++ $(CFLAGS) -c src/main.cpp -o src/main.o

Mandelbrot.o: src/Mandelbrot.h Mandelbrot.cpp 
	g++ $(CFLAGS) -c src/Mandelbrot.cpp -o src/Mandelbrot.o

Application.o: src/Application.h src/Application.cpp
	g++ $(CFLAGS) -c src/Application.cpp -o src/Application.o

Timer.o: src/Timer.h src/Timer.cpp
	g++ $(CFLAGS) -c src/Timer.cpp -o src/Timer.o

clean:
	rm src/*.o

run:
	build/project
