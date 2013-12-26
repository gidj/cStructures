#ifndef ARRAY_H_
#define ARRAY_H_ 

typedef struct array *array;

extern array array_create(int length, int size);
extern void array_free(array *array);

extern int array_length(array array);
extern int array_size(array array);

extern void *array_get(array array, int i);
extern void *array_put(array array, int i, void *elem);
extern void *array_put_auto(array array, int i, void *elem);

extern void array_resize(array array, int size);
extern array array_copy(array source);

#endif