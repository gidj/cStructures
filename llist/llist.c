#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
  struct node* next;
  int data;
} node;

typedef struct llist {
  node* head;
  node* tail;
} llist;

llist* createList(int);
void appendEnd(llist*, int);
void printList(llist*); 

int main(int argc, char *argv[])
{
  llist *myList = createList(100);
  for (int i = 0; i < 20; ++i)
  {
    appendEnd(myList, i);
  }
  
  printList(myList);

  return 0;
}

llist* createList(int number) 
{
  llist *newList = malloc(sizeof(llist));
  assert(newList != NULL);

  node* elem = (node *) malloc(sizeof(node));
  assert(elem != NULL);

  elem->data = number;
  elem->next = NULL;

  newList->head = elem;
  newList->tail = elem;
  return newList;
}

void appendEnd(llist* list, int number)
{
  node* elem = (node *) malloc(sizeof(node));
  assert(elem != NULL);

  elem->data = number;
  elem->next = NULL;

  list->tail->next = elem;
  list->tail = elem;
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
