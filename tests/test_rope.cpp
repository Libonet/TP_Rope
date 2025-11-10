#include "test_rope.h"

#include <string>
#include <vector>
#include "ropeint.h"
#include "rope.h"

#include "print_assert.h"

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
  printf("Iniciando: test_ropeint\n");

  std::vector<int> vect = {3, 7, -1, -1, 9};
  RopeInt rope(5, vect);

  
  print_assert(rope.sum(0, 5), 17);
  print_assert(rope.sum(0, 3), 9);
  print_assert(rope.sum(2, 5), 7);
  print_assert(rope.sum(5, 8), 0);

  rope.update(2, 1);

  print_assert(rope.sum(2, 4), 0);
  print_assert(rope.sum(2, 5), 9);
  print_assert(rope.sum(0, 2), 10);

  printf("Pasaron los tests de rope int!\n\n");
}

void test_genrope_int() {
  printf("Iniciando: test_genrope_int\n");

  std::vector<int> vect = {3, 7, -1, -1, 9};
  Rope<int_suma> rope(5, vect);

  
  print_assert(rope.sum(0, 5), 17);
  print_assert(rope.sum(0, 3), 9);
  print_assert(rope.sum(2, 5), 7);
  print_assert(rope.sum(5, 8), 0);

  rope.update(2, 1);

  print_assert(rope.sum(2, 4), 0);
  print_assert(rope.sum(2, 5), 9);
  print_assert(rope.sum(0, 2), 10);

  printf("Pasaron los tests de gen rope int!\n\n");
}

void test_genrope_string() {
  printf("Iniciando test_genrope_string\n");

  std::vector<std::string> vect = {"a", "b", "c", "d", "e"};
  Rope<string_concat> rope(5, vect);
  
  print_assert<std::string>(rope.sum(0, 5), "abcde");
  print_assert<std::string>(rope.sum(0, 3), "abc");
  print_assert<std::string>(rope.sum(2, 5), "cde");
  print_assert<std::string>(rope.sum(5, 8), "");

  rope.update(2, "z");

  print_assert<std::string>(rope.sum(2, 4), "zd");
  print_assert<std::string>(rope.sum(2, 5), "zde");
  print_assert<std::string>(rope.sum(0, 2), "ab");

  printf("Pasaron los tests de gen rope string!\n\n");
}

void all_rope_tests() {
  test_ropeint();
  test_genrope_int();
  test_genrope_string();
}
