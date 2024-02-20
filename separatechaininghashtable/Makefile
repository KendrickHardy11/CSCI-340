CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic -g

all: hash

hash: hashmain.cc htable.cc
	g++ $(CXXFLAGS)  htable.cc hashmain.cc -o hash

clean: 
	rm -f hash

world: clean all
