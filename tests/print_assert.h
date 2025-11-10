#ifndef PRINT_ASSERT
#define PRINT_ASSERT

#include <iostream>
#include <assert.h>

template<typename T>
void print_assert(T result, T expect) {
  std::cout << "result=" << result << "; expect=" << expect << "\n";
  assert(result == expect);
}

#endif // PRINT_ASSERT
