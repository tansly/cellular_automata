CXX=clang++
CXXFLAGS=-Wall -ggdb -I./src -std=c++14 -O3
LDFLAGS=-lncurses

test_screen.out: ./src/curses/screen.o ./src/curses/screen.h ./src/test/test_screen.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) ./src/curses/screen.o ./src/test/test_screen.o -o ./test_screen.out

predator_and_prey.out: ./src/predator_and_prey/predator_and_prey.o ./src/curses/screen.h ./src/curses/screen.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) ./src/curses/screen.o ./src/predator_and_prey/predator_and_prey.o -o ./predator_and_prey.out
