/* 
 * This implements a Heap as an abstract data structure. */ 
#include <stddef.h>

#ifndef HEAP_H_
#define HEAP_H_ 

typedef struct Heap *Heap;

extern Heap heap_init(size_t length, int size, int (*compare)(void*, void*));
extern void heap_free(Heap h);
extern void heap_push(Heap h, void* element);
extern void* heap_pop(Heap h);

extern Heap heapify(void* array, 
                    size_t length, 
                    int size, 
                    int (*compare)(void*, void*));

#endif
