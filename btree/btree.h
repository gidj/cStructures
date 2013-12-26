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
extern void  destory_tree(node tree);

extern void* value(node tree);
extern node left(node tree);
extern node right(node tree);

extern void set_key(node tree, int key);
extern void set_value(node tree, void* value);
extern void set_left(node tree, node child);
extern void set_right(node tree, node child);

extern node min(node tree);
extern node max(node tree);

extern void print_preorder(node tree);
extern void print_inorder(node tree);
extern void print_postorder(node tree);

extern node search_tree(node tree, int value);
extern void insert(node* tree, int value);
extern void delete_node(node* tree);
extern void delete_data(node tree, int value);

#endif
