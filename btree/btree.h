#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef BTREE_H_
#define BTREE_H_

typedef struct node *node;

extern node create_tree(int, node, node);
extern void  destory_tree(node);

extern int data(node);
extern node left(node);
extern node right(node);

extern void set_data(node, int);
extern void set_left(node, node);
extern void set_right(node, node);

extern node min(node);
extern node max(node);

extern void print_preorder(node tree);
extern void print_inorder(node tree);
extern void print_postorder(node tree);

extern node search_tree(node, int);
extern void insert(node*, int);
extern void delete_node(node*);
extern void delete_data(node, int);

#endif
