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

/* Helper functions that define the parent and children 'nodes' of the heap */ 

static size_t parent(size_t i) { return (i - 1) / 2; }
static size_t left(size_t i) { return 2*i + 1; }
static size_t right(size_t i) { return 2*i + 2; }

static void upheap(Heap h, size_t parent, size_t child);
static void downheap(Heap h, size_t parent, size_t child);



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




