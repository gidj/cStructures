#include "btree.h"

node* create_tree(int value)
{
  node* new_node = (node*) malloc(sizeof(node));
  assert(new_node != NULL);

  set_value(new_node, value);
  set_left(new_node, NULL);
  set_right(new_node, NULL);

  return new_node;
}

void destroy_tree(node* tree)
{
  if (tree)
  {
    destroy_tree(get_left(tree));
    destroy_tree(get_right(tree));

    free(tree);
  }
}

int get_value(node* tree)
{
  return tree->value;
}

node* get_left(node* tree)
{
  return tree->left;
}

node* get_right(node* tree)
{
  return tree->right;
}

void set_value(node* tree, int value)
{
  tree->value = value;
}

void set_left(node* tree, node* child)
{
  tree->left = child;
}

void set_right(node* tree, node* child)
{
  tree->right = child;
}

