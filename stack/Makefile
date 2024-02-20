CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic -g

stack: main.cc rational.cc rational.h stack.h
	g++ $(CXXFLAGS) -o stack main.cc rational.cc

clean:
	rm -f stack
