#ifndef ARRAY_H_
#define ARRAY_H_ 

typedef struct Array *Array;

extern Array array_create(int length, int size);
extern void array_free(Array *array);

extern int array_length(Array array);
extern int array_size(Array array);

extern void *array_get(Array array, int i);
extern void *array_put(Array array, int i, void *elem);
extern void *array_put_auto(Array array, int i, void *elem);

extern void array_resize(Array array, int size);
extern Array array_copy(Array source);

#endif
