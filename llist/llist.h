#ifndef LLIST_H_
#define LLIST_H_

typedef struct node
{
    struct node* next;
    void *data;
} node;

typedef struct llist
{
    node* head;
    node* tail;
    int length;
} llist;


node* createNode(void *elem, node* nextNode);
llist* createEmptyList();
llist* createList(void *elem);
void destroyNode(node** node);
void destroyList(llist* list);

void append(llist*, void *elem);
void prepend(llist*, void *elem);
void* pop(llist*);

#endif
