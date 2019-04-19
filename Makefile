all:
	g++ -std=c++17 matrices/test.cpp -o matrices/test

test:
	./matrices/test

clean:
	rm -rf ./matrices/test
