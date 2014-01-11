#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct List {
  int length;
  int elementSize;
  Node head;
  Node tail;
};

struct Node {
  void *data;
  Node next;
};

List list_new(int elementSize)
{
  assert(elementSize > 0);
  List new_list = malloc(sizeof(*new_list));

  new_list->length = 0;
  new_list->elementSize = elementSize;
  new_list->head = new_list->tail = NULL;

  return new_list;
}

void list_destroy(List *list)
{
  assert(list && *list);
  Node current;

  while((*list)->head) {
    current = (*list)->head;
    (*list)->head = current->next;
    free(current->dat);
    free(current);
  }

  free(*list);
  *list = NULL;
}

void list_append(List list, void *element)
{
  assert(list);
  assert(element);

  Node new_node = malloc(sizeof(*new_node));
  new_node->data = malloc(list->elementSize);
  memcpy(new_node->data, element, list->elementSize);

  new_node->next = NULL;

  if (list->length == 0)
  {
    list->head = list->tail = new_node;
  } 
  else 
  {
    list->tail->next = new_node;
    list->tail = new_node;
  }
    
  list->length++;
}

void list_prepend(List list, void *element)
{
  assert(list);
  assert(element);

  Node new_node = malloc(sizeof(*new_node));
  new_node->data = malloc(list->elementSize);
  memcpy(new_node->data, element, list->elementSize);
  
  new_node->next = list->head;
  list->head = new_node;

  if (!list->tail)
  {
    list->tail = new_node;
  }

  list->length++;
}


int list_length(List list)
{
  return list->length;
}

void* list_head(List list, void *element, bool removeElement)
{
  assert(list->head);

  memcpy(element, list->head->data, list->elementSize);

  if (removeElement)
  {
    Node elem = list->head;
    list->head = list->head->next;
    free(elem->data);
    free(elem);
    list->length--;
  }
  
  return element;
}

void* list_tail(List list, void *element)
{
  assert(list->tail);
  memcpy(element, list->tail->data, list->elementSize);
  return element;
}

void* list_peek(List list)
{
  return list->head->data;
}

void* node_data(Node node)
{
  return node->data;
}


