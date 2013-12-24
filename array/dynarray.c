#include "dynarray.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct array {
  int length;
  int size;
  char * arr;
};

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
    
 /* Because realloc() doesn't guarantee that new memory blocks will be 
  * filled with zeros like the called to calloc() does when the array is 
  * first formed, set all subsequent bytes in the array to 0.
  * */ 

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
