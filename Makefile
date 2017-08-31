# TODO: Write a proper Makefile, this is an abomination

CXX=clang++
CXXFLAGS=-Wall -ggdb -I./src -std=c++14 -O0
LDFLAGS=-lncurses

./src/curses/screen.o: ./src/curses/screen.cpp ./src/curses/screen.h

./src/predator_and_prey/predator_and_prey.o: ./src/predator_and_prey/predator_and_prey.cpp ./src/grid/grid.h

test_screen.out: ./src/curses/screen.o ./src/curses/screen.h ./src/test/test_screen.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) ./src/curses/screen.o ./src/test/test_screen.o -o ./test_screen.out

predator_and_prey.out: ./src/predator_and_prey/predator_and_prey.o ./src/curses/screen.h ./src/curses/screen.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) ./src/curses/screen.o ./src/predator_and_prey/predator_and_prey.o -o ./predator_and_prey.out
