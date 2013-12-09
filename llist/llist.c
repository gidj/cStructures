#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "llist.h"

/* A basic singly-linked list implementation for integers. To make many 
 * operations easier, each list has a first element that contains metadata 
 * about the list itself. */ 

/* The createNode() and createEmptyList() are basic constructor functions that are 
 * used in the remainder of the functions here. */ 

node* createNode(int number, node* nextNode)
{
  node* newNode = (node *) malloc(sizeof(node));
  assert(newNode != NULL);

  newNode->data = number;
  newNode->next = nextNode;

  return newNode;
}

llist* createEmptyList() 
{
  llist *newList = malloc(sizeof(llist));
  assert(newList != NULL);

  newList->head = NULL;
  newList->tail = NULL;
  newList->length = 0;

  return newList;
}

/* The destroyNode() and destroyList() are destructor methods that make sure 
 * the memory that is allocated to a list is freed properly. */ 

void destroyNode(node* node)
{
  free(node);
}

void destroyList(llist* list)
{
  node* head = list->head;

  while(head) {
    node* temp = head->next;
    destroyNode(head);
    head = temp;
  }

  free(list);
}

llist* createList(int number) 
{
  llist* newList = createEmptyList();
  node* newNode = createNode(number, NULL);
  
  newList->head = newNode;
  newList->tail = newNode;
  newList->length = 1;

  return newList;
}

/* append() and prepend() insert a new node with the value 'number' into the 
 * linked list 'list' */ 

void append(llist* list, int number)
{
  node* newNode = createNode(number, NULL);

  if (list->length == 0) 
  {
    list->head = newNode;
  } else {
    list->tail->next = newNode;
  }

  list->tail = newNode;
  list->length += 1;
}

void prepend(llist* list, int number)
{
  node* newNode = createNode(number, list->head);

  if (list->length == 0)
  {
    list->tail = newNode;
  }

  list->head = newNode;
  list->length += 1;
}

int pop(llist* list)
{
  int value = list->head->data;
  node* temp = list->head;

  if (list->head == list->tail)
  {
    list->tail = NULL;
  }

  list->head = list->head->next;
  destroyNode(temp);

  return value;
}

void printList(llist* list) 
{
  node* node;
  node = list->head;

  while(node) {
    printf("%d, ", node->data);
    node = node->next;
  }
  printf("\n");
}
