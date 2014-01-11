#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "../array/array.h"

struct Heap {
  int elementSize;
  size_t length;
  Array data_array;
  int (*cmp)();
};

/* Helper functions that define the parent and children 'nodes' of the heap */ 

static size_t parent_i(size_t i) { return (i - 1) / 2; }
static size_t left_i(size_t i) { return 2*i + 1; }
static size_t right_i(size_t i) { return 2*i + 2; }

static void upheap(Heap h, size_t node)
{
  if (node > 0)
  {
    size_t parent = parent_i(node);
    size_t child = node;

    switch(h->cmp(array_get(h->data_array, parent),
                  array_get(h->data_array, child)))
    {
      case -1:
        array_swap(h->data_array, parent, child);
        upheap(h, parent);
        return;
      case 1:
        return;
      case 0:
        return;
      default:
        printf("Something went wrong in the comparison; exiting...\n");
        exit(EXIT_FAILURE);
    }
  }
}

static void downheap(Heap h, size_t node)
{

/* Revise this to check whether the indices for left and right children are 
 * out of bounds for the heap at the BEGINNING of the function. It will make 
 * the logic cleaner. */ 

  size_t parent = node;
  size_t l = left_i(node);
  size_t r = right_i(node);
  void* array = h->data_array;

  if (h->cmp(array_get(array, parent), array_get(array, l)) == -1 || 
      h->cmp(array_get(array, parent), array_get(array, r)) == -1)
  {
    if (h->cmp(array_get(array, l), array_get(array, r)) == 1)
    {
      array_swap(array, parent, l);
      if (left_i(l) < h->length)
      {
        downheap(h, l);
      }
    }
    else
    {
      array_swap(array, parent, r);
      if (right_i(r) < h->length)
      {
        downheap(h, r);
      }
    }
  }
}

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

extern void heap_free(Heap *h)
{
  assert(h && *h);
  void* arr = (*h)->data_array;
  array_free(arr);
  free(*h);
  *h = NULL;
}

extern void heap_push(Heap h, void* element)
{
  assert(h && element);
  array_put_auto(h->data_array, h->length, element);
  upheap(h, h->length);
  h->length++;
}

extern void* heap_pop(Heap h)
{
  if (h->length == 0) { return NULL; }

  void* element = malloc(h->elementSize);
  memcpy(element, array_get(h->data_array, 0), h->elementSize);
  array_put(h->data_array, 0, array_get(h->data_array, h->length - 1));
  downheap(h, 0);

  h->length--;
  return element;
}

extern void* heap_peek(Heap h)
{
  if (h->length == 0) { return NULL; }
  return array_get(h->data_array, 0);
}

extern Heap heapify(void* array, 
                    size_t length, 
                    int size, 
                    int (*compare)(void*, void*))
{

}

Array heap_sort(Heap h)
{
  Array sorted_array = array_create(h->length, h->elementSize);
  
  void* elem;

  while(h->len) {
    /* code */
  }
} 

Array heap_get_array(Heap h)
{
  return h->data_array;
}




