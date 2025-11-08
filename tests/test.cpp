#include "ropeint.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "rope.h"
#include "lazyropeint.h"
#include "lazyrope.h"
#include <limits.h>

#include <iostream>

template<typename T>
void print_assert(T result, T expect) {
  std::cout << "result=" << result << "; expect=" << expect << "\n";
  assert(result == expect);
}

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

void test_lazyropeint() {
  printf("Iniciando test_lazyropeint\n");

  std::vector<int> vect = {3, 7, -1, -1, 9};
  LazyRopeInt rope(5, vect);

  
  print_assert(rope.sum(0, 5), 17);
  print_assert(rope.sum(0, 3), 9);
  print_assert(rope.sum(2, 5), 7);
  print_assert(rope.sum(5, 8), 0);

  rope.update(2, 5, 3);

  print_assert(rope.sum(0, 5), 26);
  print_assert(rope.sum(2, 4), 4);
  print_assert(rope.sum(2, 5), 16);
  print_assert(rope.sum(0, 2), 10);

  printf("Pasaron los tests de lazy rope int!\n\n");
}

int checkedSum(int x, int y) {
  int res = x + y;

  if (x < 0 && y < 0) {
    if (res > 0) {
      return INT_MIN;
    } else {
      return res;
    }
  }
  if (x > 0 && y > 0) {
    if (res < 0) {
      return INT_MAX;
    } else {
      return res;
    }
  }

  return res;
}

struct int_maximo {
  using Value = int;
  using Update = int;
  static int query(int x, int y) { return x > y ? x : y; } // una operacion asociativa
  static int neutQ() { return INT_MIN; } // elemento neutro para query
  static int update(int x, int y) { return checkedSum(x, y); }
  static int neutU() { return 0; }
  static int apply(int up, int val, int len) { return checkedSum(up, val); }
};

struct lazy_int_suma {
  using Value = int;
  using Update = int;
  static int query(int x, int y) { return checkedSum(x, y); } // una operacion asociativa
  static int neutQ() { return 0; } // elemento neutro para query
  static int update(int x, int y) { return checkedSum(x, y); }
  static int neutU() { return 0; }
  static int apply(int up, int val, int len) { 
    int res = val;
    for (int i = 0; i < len; i++) {
      res = checkedSum(res, up);
    }
    return res;
  }
};

void test_lazyrope_gen_int_max() {
  printf("Iniciando test_lazyrope_gen_int_max\n");

  std::vector<int> vect = {3, 7, -1, -1, 9};
  LazyRope<int_maximo> rope(vect.size(), vect);
  
  print_assert(rope.query(0, 5), 9);
  print_assert(rope.query(0, 3), 7);
  print_assert(rope.query(2, 5), 9);
  // print_assert(rope.query(5, 8) == 0);

  // 3, 7, 8, 8, 9
  rope.update(2, 4, 9);

  print_assert(rope.query(0, 5), 9);
  print_assert(rope.query(2, 4), 8);
  print_assert(rope.query(2, 5), 9);
  print_assert(rope.query(0, 2), 7);
  print_assert(rope.query(0, 3), 8);

  printf("Pasaron los tests de lazy rope generico maximo!\n\n");
}

void test_lazyrope_gen_int_suma() {
  printf("Iniciando test_lazyrope_gen_int_suma\n");

  std::vector<int> vect = {3, 7, -1, -1, 9};
  LazyRope<lazy_int_suma> rope(vect.size(), vect);

  print_assert(rope.query(0, 5), 17);
  print_assert(rope.query(0, 3), 9);
  print_assert(rope.query(2, 5), 7);
  print_assert(rope.query(5, 8), 0);

  rope.update(2, 5, 3);

  print_assert(rope.query(0, 5), 26);
  print_assert(rope.query(2, 4), 4);
  print_assert(rope.query(2, 5), 16);
  print_assert(rope.query(0, 2), 10);

  printf("Pasaron los tests de lazy rope generico suma!\n\n");
}

int main (int argc, char *argv[]) {
    test_ropeint();
    test_genrope_int();
    test_genrope_string();
    test_lazyropeint();
    test_lazyrope_gen_int_max();
    test_lazyrope_gen_int_suma();
    return 0;
}

