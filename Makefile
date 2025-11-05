CXX = g++
CXXFLAGS = -Wall -std=c++20 -Ilib
LDFLAGS = 

TEST_NAMES = $(wildcard tests/*)
TESTS_O = $(TEST_NAMES:tests%.cpp=build%.o)
ROPES = $(wildcard lib/*.h)

all: test
.PHONY: all clean run

test: $(TESTS_O) build/ropeint.o
	@echo "Linking tests"
	$(CXX) $(LDFLAGS) $^ -o test

build/test.o: $(TEST_NAMES) $(ROPES)
	@echo "Building tests"
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o ./build/test.o

build/ropeint.o: lib/ropeint.cpp lib/ropeint.h
	@echo "Building ropeint"
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c ./lib/ropeint.cpp -o ./build/ropeint.o

run: test
	@echo "Running tests"
	./test

clean:
	@echo "Removing build artifacts"
	rm -r build
