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

#define parent_i(i) ((i-1)/2) 
#define left_i(i)   (2*i + 1)
#define right_i(i)  (2*i + 2)

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
  size_t parent = node;
  size_t left = left_i(node);
  size_t right = right_i(node);
  void* array = h->data_array;

/* In the case that the left child index is greater than the length of the array
 * representing the heap, then the end of the heap has been reached and it is 
 * safe to return. */ 
  if (left > h->length)
  {
    return;
  }

/* If the right child index falls out of the bounds of the heap, only the left
 * child needs to be check to maintain the heap property. */ 
  else if (right > h->length)
  {
    switch(h->cmp(array_get(array, parent),
                  array_get(array, left)))
    {
      case -1:
        array_swap(array, parent, left);
        downheap(h, left);
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

/* If this case is reached, it means that the parent node has two children. 
 * First the two children are compared against each other, and which ever is
 * is found to be "greater than" due to the comparison function is compared
 * to the parent. */ 
  else 
  {
    switch(h->cmp(array_get(array, left), array_get(array, right)))
    {
      case 1:
        if (h->cmp(array_get(array, parent), array_get(array, left)) == -1)
        {
          array_swap(array, parent, left);
          downheap(h, left);
        }
        return;
      case -1:
        if (h->cmp(array_get(array, parent), array_get(array, right)) == -1)
        {
          array_swap(array, parent, right);
          downheap(h, right);
        }
        return;
      case 0:
        return;
      default:
        printf("Something went wrong in the comparison; exiting...\n");
        exit(EXIT_FAILURE);
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
  if (h->length == 0) 
  { 
    return NULL; 
  }
  else 
  {
    void* element = malloc(h->elementSize);
    memcpy(element, array_get(h->data_array, 0), h->elementSize);
    array_put(h->data_array, 0, array_get(h->data_array, --(h->length)));  
    downheap(h, 0);
    return element;
  }
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
  assert(h);
  if (h->length == 0) 
  { 
    return NULL; 
  }
  else
  {
    Array sorted_array = array_create(h->length, h->elementSize);
    void* elem = heap_pop(h);
    size_t i = 0;

    while(elem != NULL) {
      printf("%ld\n", *(long*)array_put(sorted_array, i++, elem));
      free(elem);
      elem = heap_pop(h);
    }

    return sorted_array;
  }
} 

Array heap_get_array(Heap h)
{
  return h->data_array;
}

