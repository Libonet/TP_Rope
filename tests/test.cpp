#include "../lib/ropeint.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <concepts>
#include "../lib/rope.h"

struct int_suma {
  using Value = int;
  static int op(int x, int y) { return x + y; } // una operacion asociativa
  static int neut() { return 0; } // elemento neutro para op
};

struct string_concat {
  using Value = std::string;
  static std::string op(std::string x, std::string y) { return x + y; } // una operacion asociativa
  static std::string neut() { return ""; } // elemento neutro para op
};

void test_ropeint() {
  std::vector<int> vect = {3, 7, -1, -1, 9};
  RopeInt rope(5, vect);

  
  assert(rope.sum(0, 5) == 17);
  assert(rope.sum(0, 3) == 9);
  assert(rope.sum(2, 5) == 7);
  assert(rope.sum(5, 8) == 0);

  rope.update(2, 1);

  assert(rope.sum(2, 4) == 0);
  assert(rope.sum(2, 5) == 9);
  assert(rope.sum(0, 2) == 10);

  printf("Pasaron los tests de rope int!\n");
}

void test_genrope_int() {
  std::vector<int> vect = {3, 7, -1, -1, 9};
  Rope<int_suma> rope(5, vect);

  
  assert(rope.sum(0, 5) == 17);
  assert(rope.sum(0, 3) == 9);
  assert(rope.sum(2, 5) == 7);
  assert(rope.sum(5, 8) == 0);

  rope.update(2, 1);

  assert(rope.sum(2, 4) == 0);
  assert(rope.sum(2, 5) == 9);
  assert(rope.sum(0, 2) == 10);

  printf("Pasaron los tests de gen rope int!\n");
}

void test_genrope_string() {
  std::vector<std::string> vect = {"a", "b", "c", "d", "e"};
  Rope<string_concat> rope(5, vect);

  
  assert(rope.sum(0, 5) == "abcde");
  assert(rope.sum(0, 3) == "abc");
  assert(rope.sum(2, 5) == "cde");
  assert(rope.sum(5, 8) == "");

  rope.update(2, "z");

  assert(rope.sum(2, 4) == "zd");
  assert(rope.sum(2, 5) == "zde");
  assert(rope.sum(0, 2) == "ab");

  printf("Pasaron los tests de gen rope string!\n");
}

int main (int argc, char *argv[]) {
    test_ropeint();
    test_genrope_int();
    test_genrope_string();
    return 0;
}

