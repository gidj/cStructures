#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "llist.h"

/* A basic singly-linked list implementation for generic types. To make many 
 * operations easier, each list has a first element that contains metadata 
 * about the list itself. */ 

/* The createNode() and createEmptyList() are basic constructor functions that are 
 * used in the remainder of the functions here. */ 

node* createNode(void *elem, node* nextNode)
{
  node* newNode = malloc(sizeof(node));
  assert(newNode);

  newNode->data = elem;
  newNode->next = nextNode;

  return newNode;
}

llist* createEmptyList() 
{
  llist *newList = malloc(sizeof(llist));
  assert(newList);

  newList->head = NULL;
  newList->tail = NULL;
  newList->length = 0;

  return newList;
}

/* The destroyNode() and destroyList() are destructor methods that make sure 
 * the memory that is allocated to a list is freed properly. */ 

void destroyNode(node** dead)
{
  node* temp = *dead;
  (*dead) = (*dead)->next;
  free(temp);
}

void destroyList(llist* list)
{
  node* head = list->head;

  while(head) {
    node* temp = head->next;
    free(head);
    head = temp;
  }

  free(list);
}

llist* createList(void *elem) 
{
  llist* newList = createEmptyList();
  node* newNode = createNode(elem, NULL);
  
  newList->head = newNode;
  newList->tail = newNode;
  newList->length = 1;

  return newList;
}

/* append() and prepend() insert a new node with the value 'number' into the 
 * linked list 'list' */ 

void append(llist* list, void *elem)
{
  node* newNode = createNode(elem, NULL);

  if (list->length == 0) 
  {
    list->head = newNode;
  } else {
    list->tail->next = newNode;
  }

  list->tail = newNode;
  list->length += 1;
}

void prepend(llist* list, void *elem)
{
  node* newNode = createNode(elem, list->head);

  if (list->length == 0)
  {
    list->tail = newNode;
  }

  list->head = newNode;
  list->length += 1;
}

void* pop(llist* list)
{
  void* value = list->head->data;
  node* temp = list->head;

  if (list->head == list->tail)
  {
    list->tail = NULL;
  }

  list->head = list->head->next;
  free(temp);

  return value;
}

