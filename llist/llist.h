#ifndef LLIST_H_
#define LLIST_H_

typedef struct node
{
    struct node* next;
    int data;
} node;

typedef struct llist
{
    node* head;
    node* tail;
    int length;
} llist;


node* createNode(int, node*);
llist* createEmptyList();
llist* createList(int);
void destroyNode(node*);
void destroyList(llist*);

void append(llist*, int);
void prepend(llist*, int);
int pop(llist*);
void printList(llist*);

#endif
