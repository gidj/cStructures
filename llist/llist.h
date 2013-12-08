#ifndef LLIST_H
#define LLIST_H 

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

#endif
