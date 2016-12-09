CXX=            g++-4.8
CXXFLAGS=       -g -Wall -std=gnu++11
SHELL=          bash
MEASURE=        ../common/measure
PREFIX=         shortestpath/dijkstras
CHECK=		mapmaker/primCheck
TEST_DIR=       ./test

all:           $(PREFIX)

$(PREFIX):       $(PREFIX).cpp
		$(CXX) $(CXXFLAGS) -o $@ $^

$(CHECK):	$(CHECK).cpp
		$(CXX) $(CXXFLAGS) -o $@ $^
clean:
	        rm -f $(PREFIX)
		rm -f $(CHECK)

test:           test-output test-memory 

test-output:    all
	        @echo Testing output...
		        @diff --suppress-common-lines -y <($(PREFIX) < $(TEST_DIR)/input) $(TEST_DIR)/output

test-memory:    all
	        @echo Testing memory...
		        @[ `valgrind --leak-check=full $(PREFIX) < $(TEST_DIR)/input 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]

test-connected: all
		@echo Testing connectivity...
			./mapmaker/primCheck
get-deps:
	sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
	sudo apt-get -qq update
	sudo apt-get -qq install g++-4.8
	sudo apt-get -qq install valgrind
