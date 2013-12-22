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

void array_resize(array array, int size)
{

}

array array_copy(array array)
{
  assert(array);
  array copy = array_create(array->length, array->size);
  
  if (copy->length >= array->length && array->length > 0)
  {
    memcpy(copy->arr, array->arr, array->length*array->size); 
  }
  else if (array->length > copy->length && copy->length > 0)
  {
    memcpy(copy->arr, array->arr, copy->length*array->size); 
  }

  return copy;
}
