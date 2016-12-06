CXX=            g++
CXXFLAGS=       -g -Wall -std=gnu++11
SHELL=          bash
MEASURE=        ../common/measure

all:           shortestpath/djikstras

solution:       shortestpath/djikstras.cpp
	        $(CXX) $(CXXFLAGS) -o $@ $^

clean:
	        rm -f djikstras

test:           test-output test-memory 

test-output:    solution
	        @echo Testing output...
		        @diff --suppress-common-lines -y <(./solution < input) output

test-memory:    solution
	        @echo Testing memory...
		        @[ `valgrind --leak-check=full ./solution < input 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]

