#include "../lib/ropeint.h"
#include <assert.h>
#include <stdio.h>
#include <vector>

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

int main (int argc, char *argv[]) {
    test_ropeint();
    return 0;
}

