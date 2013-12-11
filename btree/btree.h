#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef BTREE_H_
#define BTREE_H_

typedef struct node {
    struct node* left;
    struct node* right;
    int data;
} node;

node* create_tree(int, node*, node*);
void  destory_tree(node*);

int data(node*);
node* left(node*);
node* right(node*);

void set_data(node*, int);
void set_left(node*, node*);
void set_right(node*, node*);

node* min(node*);
node* max(node*);

void print_preorder(node* tree);
void print_inorder(node* tree);
void print_postorder(node* tree);

node* search_tree(node*, int);
node* insert(node*, int);
node* delete_node(node*);
node* delete_data(node*, int);

#endif
