#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef BTREE_H_
#define BTREE_H_

typedef struct node {
    struct node* left;
    struct node* right;
    int value;
} node;

node* create_tree(int, node*, node*);
void  destory_tree(node*);

int get_value(node*);
node* get_left(node*);
node* get_right(node*);

void set_value(node*, int);
void set_left(node*, node*);
void set_right(node*, node*);

void print_preorder(node* tree);
void print_inorder(node* tree);
void print_postorder(node* tree);

node* search_tree(node*, int);
node* insert(node*, int);

#endif
