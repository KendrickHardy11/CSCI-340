CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic -g

all: wordscanner

wordscanner: wordscanner.cc
	g++ $(CXXFLAGS) -o wordscanner wordscanner.cc

clean:
	rm -f wordscanner

world: clean all
