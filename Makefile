CXX = g++
CXXFLAGS = -Wall -std=c++20
LDFLAGS = 

all: test
.PHONY: all clean run

test: build/test.o build/rope.o
	@echo "Linking tests"
	$(CXX) $(LDFLAGS) ./build/rope.o ./build/test.o -o test

build/test.o: $(wildcard tests/*.cpp)
	@echo "Building tests"
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $^ -o ./build/test.o

build/rope.o: lib/rope.cpp lib/rope.h
	@echo "Building rope"
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c ./lib/rope.cpp -o ./build/rope.o

run: test
	@echo "Running tests"
	./test

clean:
	@echo "Removing build artifacts"
	rm -r build
