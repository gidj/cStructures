#include <stddef.h>
#ifndef ARRAY_H_
#define ARRAY_H_ 

typedef struct Array *Array;

extern Array array_create(size_t length, int size);
extern void array_free(Array *array);

extern int array_length(Array array);
extern int array_size(Array array);

extern void *array_get(Array array, size_t i);
extern void *array_put(Array array, size_t i, void *elem);
extern void *array_put_auto(Array array, size_t i, void *elem);

extern void array_resize(Array array, size_t length);
extern void array_swap(Array array, size_t i, size_t j);
extern Array array_copy(Array source);

#endif
