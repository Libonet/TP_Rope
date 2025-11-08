#include "ropeint.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <concepts>
#include "rope.h"
#include "lazyropeint.h"
#include "lazyrope.h"
#include "limits.h"

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

struct lazy_int_suma {
  using Value = int;
  using Update = int;
  static int query(int x, int y) { return x + y; } // una operacion asociativa
  static int neutQry() { return 0; } // elemento neutro para query
  static int update(int x, int y) { return x + y; } // una operacion conmutativa y asociativa
  static int neutUpd() { return 0; } // elemento neutro para update
  static int apply(int x, int y, int len) { return x + y * len;}
};

struct int_maximo {
  using Value = int;
  using Update = int;
  static int query(int x, int y) { return x > y ? x : y; } // una operacion asociativa
  static int neutQry() { return INT_MIN; } // elemento neutro para op
  static int update(int x, int y) { 
    if (x == INT_MIN || y == INT_MIN)
      return INT_MIN;
    else
      return x + y;
  } // una operacion conmutativa y asociativa
  static int neutUpd() { return 0; } // elemento neutro para update
  static int apply(int x, int y, int len) { return update(x, y); }
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

void test_lazyropeint() {
  std::vector<int> vect = {3, 7, -1, -1, 9};
  LazyRopeInt rope(5, vect);

  
  assert(rope.sum(0, 5) == 17);
  assert(rope.sum(0, 3) == 9);
  assert(rope.sum(2, 5) == 7);
  assert(rope.sum(5, 8) == 0);

  rope.update(2, 5, 3);

  assert(rope.sum(0, 5) == 26);
  assert(rope.sum(2, 4) == 4);
  assert(rope.sum(2, 5) == 16);
  assert(rope.sum(0, 2) == 10);

  printf("Pasaron los tests de lazy rope int!\n");
}

void test_genlazyrope_sumint() {
  std::vector<int> vect = {3, 7, -1, -1, 9};
  LazyRope<lazy_int_suma> rope(5, vect);

  
  assert(rope.query(0, 5) == 17);
  assert(rope.query(0, 3) == 9);
  assert(rope.query(2, 5) == 7);
  assert(rope.query(5, 8) == 0);

  rope.update(2, 5, 3);

  assert(rope.query(0, 5) == 26);
  assert(rope.query(2, 4) == 4);
  assert(rope.query(2, 5) == 16);
  assert(rope.query(0, 2) == 10);

  printf("Pasaron los tests de gen lazy rope int!\n");
}

void test_genlazyrope_maxint() {
  std::vector<int> vect = {3, 7, -1, -1, 9};
  LazyRope<int_maximo> rope(5, vect);

  assert(rope.query(0, 5) == 9);
  assert(rope.query(0, 3) == 7);
  assert(rope.query(2, 5) == 9);
  
  // {3, 7, 10, 10, 9}
  rope.update(2, 4, 11);
  
  assert(rope.query(0, 5) == 10);
  assert(rope.query(2, 4) == 10);
  assert(rope.query(2, 5) == 10);
  assert(rope.query(0, 2) == 7);
  assert(rope.query(0, 3) == 10);

  printf("Pasaron los tests de gen lazy rope max!\n");
}

int main (int argc, char *argv[]) {
    test_ropeint();
    test_genrope_int();
    test_genrope_string();
    test_lazyropeint();
    test_genlazyrope_sumint();
    test_genlazyrope_maxint();
    return 0;
}

