CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic -g

all: binarytree

binarytree: binarytree.cc btree.h node.h
	g++ $(CXXFLAGS) -o binarytree binarytree.cc

clean:
	rm -f binarytree

world: clean all
