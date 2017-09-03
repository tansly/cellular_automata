# TODO: Write a proper Makefile, this is an abomination

CXX=g++-7.2.0
CXXFLAGS=-Wall -Wextra -ggdb -I./src -std=c++17 -O3
LDFLAGS=-lncurses

./src/curses/screen.o: ./src/curses/screen.cpp ./src/curses/screen.h

test_screen.out: ./src/curses/screen.o ./src/curses/screen.h ./src/test/test_screen.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) ./src/curses/screen.o ./src/test/test_screen.o -o ./test_screen.out

./src/automata/predator_and_prey.o: ./src/automata/predator_and_prey.cpp ./src/automata/predator_and_prey.h ./src/curses/screen.o ./src/curses/screen.h ./src/grid/grid.h ./src/grid/toroidal_grid.h

./src/automata/life.o: ./src/automata/life.cpp ./src/automata/life.h ./src/curses/screen.o ./src/curses/screen.h ./src/grid/grid.h ./src/grid/toroidal_grid.h

./src/automata/life_like.o: ./src/automata/life_like.cpp ./src/automata/life_like.h ./src/curses/screen.o ./src/curses/screen.h ./src/grid/grid.h ./src/grid/toroidal_grid.h

predator_and_prey.out: ./src/test/test_predator_and_prey.cpp ./src/automata/predator_and_prey.h ./src/automata/predator_and_prey.o ./src/curses/screen.o ./src/curses/screen.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) ./src/test/test_predator_and_prey.cpp ./src/curses/screen.o ./src/automata/predator_and_prey.o -o ./predator_and_prey.out

life.out: ./src/test/test_life.cpp ./src/automata/life.h ./src/automata/life.o ./src/curses/screen.o ./src/curses/screen.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) ./src/test/test_life.cpp ./src/curses/screen.o ./src/automata/life.o -o ./life.out

life_like.out: ./src/test/test_life_like.cpp ./src/automata/life_like.h ./src/automata/life_like.o ./src/curses/screen.o ./src/curses/screen.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) ./src/test/test_life_like.cpp ./src/curses/screen.o ./src/automata/life_like.o -o ./life_like.out
