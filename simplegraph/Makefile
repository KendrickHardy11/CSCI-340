CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic -I.

all: simplegraph

simplegraph: graph.cc simplegraph.cc graph.h
	g++ $(CXXFLAGS) -o simplegraph simplegraph.cc graph.cc

clean:
	rm -f simplegraph

world: clean all
