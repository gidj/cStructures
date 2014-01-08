#include <assert.h>
#include <stdlib.h>
#include "heap.h"
#include "../array/array.h"

struct Heap {
  int elementSize;
  size_t length;
  Array data_array;
  int (*cmp)();
};

extern Heap heap_init(int elementSize, int (*compare)(void*, void*))
{
  assert(elementSize > 0);

  Heap h = malloc(sizeof(*h));
  assert(h);

  h->elementSize = elementSize;
  h->length = 0;
  h->data_array = array_create(8, elementSize);
  h->cmp = compare;

  return h;
}

extern void heap_free(Heap h)
{
  assert(h);
  array_free(&(h->data_array));
  free(h);
}

extern void heap_push(Heap h, void* element)
{
  assert(h && element);

}

extern void* heap_pop(Heap h)
{

}

extern void* heap_peek(Heap h)
{
  return array_get(h->data_array, 0);
}

extern Heap heapify(void* array, 
                    size_t length, 
                    int size, 
                    int (*compare)(void*, void*))
{

}




