CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic -I.

all: josephus

josephus: josephus.cc josephus.h
	g++ $(CXXFLAGS) -o josephus josephus.cc


clean:
	rm -f josephus


world: clean all
