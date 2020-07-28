CXX = g++
CXXFLAGS = -Wall -g

maths_test: test.cpp basics.cpp basics.h
	$(CXX) $(CXXFLAGS) -o maths_test $^

all: clean maths_test

run: clean maths_test
	./maths_test
	
clean:
	rm -f maths_test
	
