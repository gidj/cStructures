#include "dynarray.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct array {
  int length;
  int size;
  char * arr;
};

/* array_create() and array_free() are the methods for creating and cleaning 
 * up our array object. array_create() takes the number of objects that the 
 * initial array can hold, and the size of that object in bytes. */ 

array array_create(int length, int size)
{
  assert(length >= 0);

  array new_array = malloc(sizeof(*new_array));
  assert(new_array);

  new_array->size = size;
  new_array->length = length;

  if (length > 0)
  {
    new_array->arr = calloc(length, size);
    assert(new_array->arr);
  }
  else
  {
    new_array->arr = NULL;
  }

  return new_array;
}

void array_free(array *array)
{
  assert(array && *array);
  if ((*array)->arr)
  {
    free((*array)->arr);
  }

  free(*array);
}

int array_length(array array)
{
  assert(array);
  return array->length;
}

int array_size(array array)
{
  assert(array);
  return array->size;
}

/* array_get(), array_put(), and array_put_auto() access the underlying array
 * and either get the value at the given index or put the object pointed to via
 * 'elem' into the array at the given index. It is a checked runtime error to 
 * give an index to either array_get() or array_put() that is outside the 
 * bounds of the array length, but array_put_auto() will automatically resize
 * the array if given an index that is greater than the current length of the 
 * array. */ 

void *array_get(array array, int i)
{
  assert(array);
  assert(i >= 0 && i < array->length);
  return array->arr + (array->size * i);
}

void *array_put(array array, int i, void *elem)
{
  assert(array);
  assert(i >= 0 && i < array->length);

  assert(elem);
  memcpy(array->arr + (array->size * i), elem, array->size);
  return elem;
}

void *array_put_auto(array array, int i, void * elem)
{
  assert(array);
  assert(elem);

  if (i >= array->length)
  {
    array_resize(array, (array->length * 2));
  }

  memcpy(array->arr + (array->size * i), elem, array->size);
  return elem;
}

/* If the new length given is less than the current length of the array given,
 * then the given array is truncated to the new length; if the new length is 
 * greater than the old length, the array is expanded to the new length and 
 * the new memory is written over with 0's. */ 

void array_resize(array array, int length)
{
  assert(array);

  if (length == 0)
  {
    free(array->arr);
    array->arr = NULL;
  }
  else if (array->length == 0) 
  {
    array->arr = calloc(length, array->size);
    assert(array->arr);
  }
  else 
  {
    array->arr = realloc(array->arr, length*array->size);
    
    if (length > array->length)
    {
      int diff = length - array->length;
      memset(array->arr + array->length*array->size, 0, diff*array->size);
    }
  }
  array->length = length;
}

array array_copy(array source)
{
  assert(source);
  array copy = array_create(source->length,source->size);
  
  if (copy->length >= source->length && source->length > 0)
  {
    memcpy(copy->arr, source->arr, source->length*source->size); 
  }
  else if (source->length > copy->length && copy->length > 0)
  {
    memcpy(copy->arr, source->arr, copy->length*source->size); 
  }

  return copy;
}
