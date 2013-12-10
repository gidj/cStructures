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

node* create_tree(int);
void  destory_tree(node*);

int get_value(node*);
node* get_left(node*);
node* get_right(node*);

void set_value(node*, int);
void set_left(node*, node*);
void set_right(node*, node*);


#endif
