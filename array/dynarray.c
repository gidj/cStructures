#include "dynarray.h"
#include <assert.h>
#include <stdlib.h>

struct array {
  int length;
  int size;
  char * arr;
};

array array_create(int length, int size)
{
  assert(length >= 0);

  array new_array = malloc(sizeof(array));
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
