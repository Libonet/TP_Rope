CXX = g++
CXXFLAGS = -Wall -std=c++20 -Ilib -g
LDFLAGS = 

TEST_NAMES = $(wildcard tests/*.cpp)
TESTS_O = $(TEST_NAMES:tests/%.cpp=build/%.o)
ROPES = $(wildcard lib/*.h)

all: test
.PHONY: all clean run

test: $(TESTS_O) build/ropeint.o
	@echo "Linking tests"
	$(CXX) $(LDFLAGS) $^ -o test

build/ropeint.o: lib/ropeint.cpp lib/ropeint.h
	@echo "Building ropeint"
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c ./lib/ropeint.cpp -o ./build/ropeint.o

build/%.o: tests/%.cpp $(ROPES)
	@echo "Building $@"
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@



run: test
	@echo "Running tests"
	./test

clean:
	@echo "Removing build artifacts"
	rm -r build
