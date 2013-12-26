#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef BTREE_H_
#define BTREE_H_

typedef struct node *node;

extern node create_tree(int key,
                        void* value,
                        node left, 
                        node right);
extern void  destroy_tree(node tree);

extern int key(node n);
extern void* value(node tree);
extern node left(node tree);
extern node right(node tree);

extern void key_set(node tree, int key);
extern void value_set(node tree, void* value);
extern void left_set(node tree, node child);
extern void right_set(node tree, node child);

extern node min(node tree);
extern node max(node tree);

extern void print_preorder(node tree);
extern void print_inorder(node tree);
extern void print_postorder(node tree);

extern node search_tree(node tree, int value);
extern void insert(node* tree, int key, void* value);
extern void node_delete(node* tree);
extern void data_delete(node tree, int key);

#endif
