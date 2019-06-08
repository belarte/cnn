all: matrix network

matrix:
	g++ -I. -std=c++17 -Wall -Wextra -Werror matrices/test.cpp -o matrices/test

network:
	g++ -I. -std=c++17 -Wall -Wextra -Werror network/test.cpp -o network/test

test: matrix network
	./matrices/test
	./network/test

clean:
	rm -rf ./matrices/test
	rm -rf ./network/test

.PHONY: all network test clean
