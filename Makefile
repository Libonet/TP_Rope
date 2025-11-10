CXX = g++
CXXFLAGS = -Wall -std=c++20 -Ilib -g
LDFLAGS = 

# sources
TEST_NAMES = $(wildcard tests/*.cpp)
TESTS_H = $(wildcard tests/*.h)

ROPES_CPP = $(wildcard lib/*.cpp)
ROPES_H = $(wildcard lib/*.h)

# objects
TESTS_O = $(TEST_NAMES:tests/%.cpp=build/%.o)
ROPES_O = $(ROPES_CPP:lib/%.cpp=build/%.o)

build_all: test
.PHONY: build_all clean rope lazy all

test: $(TESTS_O) $(ROPES_O)
	@echo "Linking tests"
	$(CXX) $(LDFLAGS) $^ -o test

build/%.o: lib/%.cpp $(ROPES_H)
	@echo "Building rope: $@"
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: tests/%.cpp $(TESTS_H) $(ROPES_H)
	@echo "Building $@"
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Phony commands

rope: test
	@echo "Running rope tests"
	./test "rope"

lazy: test
	@echo "Running lazyrope tests"
	./test "lazy"

all: test
	@echo "Running all tests"
	./test "all"

clean:
	@echo "Removing build artifacts"
	rm -r build
	rm test
