#include <iostream>

#include "lib/myadapters.h"

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6};

  auto removed = v | Filter([](int i) { return i % 2; });
  auto result = removed | Transform([](int i) { return i * i; });

  for (int i : result) std::cout << i << " ";
  return 0;
}