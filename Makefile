all: matrix network

matrix:
	g++ -I. -std=c++17 matrices/test.cpp -o matrices/test

network:
	g++ -I. -std=c++17 network/test.cpp -o network/test

test:
	./matrices/test
	./network/test

clean:
	rm -rf ./matrices/test
	rm -rf ./network/test

.PHONY: all network test clean
