#include "heap.h"

struct Heap {
  int elementSize;
  size_t length;
  void* data;
  int (*cmp)();
};
