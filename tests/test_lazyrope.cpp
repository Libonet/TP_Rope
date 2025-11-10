#include "test_lazyrope.h"

#include "print_assert.h"
#include "lazyropeint.h"
#include "lazyrope.h"

#include <limits.h>

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

void all_lazyrope_tests() {
  test_lazyropeint();
  test_lazyrope_gen_int_max();
  test_lazyrope_gen_int_suma();
}
