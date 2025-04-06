#yahelomessi@gmail.com

CXXFLAGS = -std=c++17 -Wall
FILES = main.cpp Graph.cpp Algorithms.cpp Queue.cpp PriorityQueue.cpp UnionFind.cpp
TEST_FILES = test.cpp Graph.cpp Algorithms.cpp Queue.cpp PriorityQueue.cpp UnionFind.cpp

all:
	g++ $(CXXFLAGS) $(FILES) -o Main

run: all
	./Main

valgrind: all
	valgrind --leak-check=full ./Main

test: $(TEST_FILES) doctest.h
	g++ $(CXXFLAGS) $(TEST_FILES) -o Test
	./Test


clean:
	rm -f Main Test
