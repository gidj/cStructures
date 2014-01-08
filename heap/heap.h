#include "../array/array.h"
#include <stddef.h>

#ifndef HEAP_H_
#define HEAP_H_ 

typedef struct Heap *Heap;

extern Heap heap_init(size_t length, int size, Array array);





#endif
