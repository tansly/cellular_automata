# TODO: Write a proper Makefile, this is an abomination

CXX=clang++
CXXFLAGS=-Wall -ggdb -I./src -std=c++14 -O3
LDFLAGS=-lncurses

./src/curses/screen.o: ./src/curses/screen.cpp ./src/curses/screen.h

test_screen.out: ./src/curses/screen.o ./src/curses/screen.h ./src/test/test_screen.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) ./src/curses/screen.o ./src/test/test_screen.o -o ./test_screen.out

./src/automata/predator_and_prey.o: ./src/automata/predator_and_prey.cpp ./src/automata/predator_and_prey.h ./src/curses/screen.o ./src/curses/screen.h ./src/grid/grid.h

predator_and_prey.out: ./src/test/test_predator_and_prey.cpp ./src/automata/predator_and_prey.h ./src/automata/predator_and_prey.o ./src/curses/screen.o ./src/curses/screen.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) ./src/test/test_predator_and_prey.cpp ./src/curses/screen.o ./src/automata/predator_and_prey.o -o ./predator_and_prey.out
