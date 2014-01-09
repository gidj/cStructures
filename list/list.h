#include <stdbool.h>

#ifndef LIST_H_
#define LIST_H_

typedef struct List *List;
typedef struct Node *Node;

extern List list_new(int elementSize);
extern void list_destroy(List *list);

extern void list_append(List list, void *element);
extern void list_prepend(List list, void *element);

extern int list_length(List list);
extern void* list_head(List list, void *element, bool removeElement);
extern void* list_tail(List list, void *element);
extern void* list_peek(List list);
extern void* node_data(Node node);

#endif
