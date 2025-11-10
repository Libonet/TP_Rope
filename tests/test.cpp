#include <cstring>
#include <limits.h>
#include "test_rope.h"
#include "test_lazyrope.h"

int main (int argc, char *argv[]) {
  if (argc == 1) {
    // run all
    all_rope_tests();
    all_lazyrope_tests();
  } else if (argc >= 2) {
    if (!strcmp(argv[1], "rope")) {
      all_rope_tests();
    }
    if (!strcmp(argv[1], "lazy")) {
      all_lazyrope_tests();
    }
    if (!strcmp(argv[1], "all")) {
      all_rope_tests();
      all_lazyrope_tests();
    }
  }

  return 0;
}

