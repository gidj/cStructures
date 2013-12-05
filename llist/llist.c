#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct intElement {
  struct intElement* next;
  int data;
} intElement;

typedef struct llist {
  intElement* head;
  intElement* tail;
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

llist* createList(int num) 
{
  llist *newList = malloc(sizeof(llist));
  assert(newList != NULL);

  intElement* elem = (intElement *) malloc(sizeof(intElement));
  assert(elem != NULL);

  elem->data = num;
  elem->next = NULL;

  newList->head = elem;
  newList->tail = elem;
  return newList;
}

void appendEnd(llist* list, int num)
{
  intElement* elem = (intElement *) malloc(sizeof(intElement));
  assert(elem != NULL);

  elem->data = num;
  elem->next = NULL;

  list->tail->next = elem;
  list->tail = elem;
}

void printList(llist* list) 
{
  intElement* node;

  node = list->head;

  while(node != NULL) {
    printf("%d\n", node->data);
    node = node->next;
  }
}
