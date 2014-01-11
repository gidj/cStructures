/* 
 * This implements a Heap as an abstract data structure. 
 *
 * heap_init() returns an empty heap; one can define either a min- or max-heap
 * by passing the appropriate compare function. The compare function must take
 * two void pointers as parameters and must return 1 if the two elements are in 
 * the right order, 0 if they are equal, and -1 if they must switch places. All
 * other returned values constitute a checked runtime error and will exit the 
 * program.
 *
 * heap_push() adds a value to the given heap
 * 
 * heap_pop() returns the the superlative value of the heap, as determined by
 * the initial compare function, and removes that element.
 *
 * heap_peek() does the same as heap_pop(), but leaves the superlative element
 * intact.
 *
 * heapify() returns a heap initialized with the values from an array, with 
 * the given compare function. 
 */ 

#include <stddef.h>

#ifndef HEAP_H_
#define HEAP_H_ 

typedef struct Heap *Heap;

extern Heap heap_init(int size, int (*compare)(void*, void*));
extern void heap_free(Heap *h);
extern void heap_push(Heap h, void* element);
extern void* heap_pop(Heap h);
extern void* heap_peek(Heap h);

extern Heap heapify(void* array, 
                    size_t length, 
                    int size, 
                    int (*compare)(void*, void*));


/* For testing purposes */ 
#include "../array/array.h"
extern Array heap_sort(Heap h);
extern Array heap_get_array(Heap h);
#endif
