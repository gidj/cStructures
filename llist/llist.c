#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* A basic singly-linked list implementation for integers. To make many 
 * operations easier, each list has a first element that contains metadata 
 * about the list itself. */ 

typedef struct node {
  struct node* next;
  int data;
} node;

typedef struct llist {
  node* head;
  node* tail;
  int length; 
} llist;

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

}

void destroyList(llist* list)
{

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
  node* newNode = createNode(number, NULL);

  if (list->length == 0)
  {
    list->tail = newNode;
  }

  newNode->next = list->head;
  list->head = newNode;
  list->length += 1;
}

node* pop(llist* list)
{


}

void printList(llist* list) 
{
  node* node;

  node = list->head;

  while(node != NULL) {
    printf("%d\n", node->data);
    node = node->next;
  }
}
