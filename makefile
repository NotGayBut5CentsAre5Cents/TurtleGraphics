all: star.o hexagon.o seirpinski.o

star.o: star.cc
	g++ -o star star.cc

hexagon.o: hexagon.cc
	g++ -o hexagon hexagon.cc

seirpinski.o: sierpinski.cc
	g++ -o sierpinski sierpinski.cc
