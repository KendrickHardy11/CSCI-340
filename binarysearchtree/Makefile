CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic -g

all: binarysearchtree

binarysearchtree: bst.cc bst.h node.h btree.h
	g++ $(CXXFLAGS) -o binarysearchtree bst.cc

clean:
	rm -f binarysearchtree

world: clean all
