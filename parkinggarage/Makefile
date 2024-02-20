CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic -g

all: parking

parking: parking.cc
	g++ $(CXXFLAGS) -o parking parking.cc

clean:
	rm -f parking

world: clean all
