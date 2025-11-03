CXX = g++
CXXFLAGS = -Wall -std=c++20 -Ilib
LDFLAGS = 

TEST_NAMES = $(wildcard tests/*)
TESTS_O = $(TEST_NAMES:tests%.cpp=build%.o)
ROPES = $(wildcard lib/*.h)

all: test
.PHONY: all clean run

test: $(TESTS_O)
	@echo "Linking tests"
	$(CXX) $(LDFLAGS) $^ -o test

build/test.o: $(TEST_NAMES) $(ROPES)
	@echo "Building tests"
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o ./build/test.o

# build/rope.o: lib/rope.cpp lib/rope.h
# 	@echo "Building rope"
# 	@mkdir -p build
# 	$(CXX) $(CXXFLAGS) -c ./lib/rope.cpp -o ./build/rope.o

run: test
	@echo "Running tests"
	./test

clean:
	@echo "Removing build artifacts"
	rm -r build
