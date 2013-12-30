#include "btree.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  int key;
  void* value;
  int elementSize;
  Node left, right;
};

Node tree_create(int key, void* value, int elementSize, Node left, Node right)
{
  assert(value);
  assert(elementSize > 0);
  
  Node node = malloc(sizeof(*node));
  node->key = key;
  node->value = malloc(elementSize);
  memcpy(node->value, value, elementSize);
  node->left = left;
  node->right = right;

  return node;
}

void tree_destroy(Node tree)
{
  assert(tree);
  Node left = tree->left;
  Node right = tree-> right;

  free(tree->value);
  free(tree);

  if (left) { tree_destroy(left); }
  if (right) { tree_destroy(right); }
}

void* min_value(Node tree)
{
  assert(tree);
  Node current = tree;
  
  while(current->left) {
    current = current->left;
  }
  return current->value;
}

void* max_value(Node tree)
{
  assert(tree);
  Node current = tree;
  
  while(current->right) {
    current = current->right;
  }
  return current->value;
}

void* tree_search(Node tree, int key)
{
  assert(tree);
  Node current = tree;

  do {
    if      (key == current->key) { return current->value; }
    else if (key < current->key) { current = current->left; } 
    else if (key > current->key) { current = current->right; }
  } while(current); 

  return NULL;
}

void tree_insert(Node tree, int key, void* value, int elementSize)
{
  assert(tree);
  Node current = tree;

  if (key == current->key)
  {
    current->value = realloc(current->value, elementSize);
    memcpy(current->value, value, elementSize);
    current->elementSize = elementSize;
    return;
  } 
  else if (key < current->key)
  { 
    if (current->left)
    {
      tree_insert(current->left, key, value, elementSize);
    } 
    else
    {
      current->left = tree_create(key, value, elementSize, NULL, NULL);
      return;
    }
  } 
  else if (key > current->key)
  {
    if (current->right)
    {
      tree_insert(current->right, key, value, elementSize);
    }
    else
    {
      current->right = tree_create(key, value, elementSize, NULL, NULL);
      return;
    }
  }
}

void tree_delete(Node tree, int key)
{
  if (tree)
  {
    if (key == tree->key)
    {
      node_delete(&tree);
    }
    else if (key < tree->key)
    {
      tree_delete(tree->left, key);
    }
    else if (key > tree->key)
    {
      tree_delete(tree->right, key);
    }
  }
  return;
}

void node_delete(Node *node)
{
  if (*node)
  {
    Node current = *node;
    
    if (!current->left && !current->right)
    {
      tree_destroy(current);
      *node = NULL;
      return;
    }
    else if (!current->left)
    {
      *node = current->right;
      free(current->value);
      free(current);
      return;
    }
    else if (!current->right)
    {
      *node = current->left;
      free(current->value);
      free(current);
      return;
    }
    else
    {
      Node successor = min_node(current->right);
      if ((*node)->right == successor)
      {
        Node temp = *node;
        successor->left = (*node)->left;
        *node = successor;

        free(temp->value);
        free(temp);
        return;
      }
      else
      {
        (*node)->key = successor->key;
        (*node)->value = successor->value;
        (*node)->elementSize = successor->elementSize;

        tree_delete((*node)->right, successor->key);
        return;
      }
    }
  }
}

Node node_left(Node node)
{
  return node->left;
}

Node node_right(Node node)
{
  return node->right;
}

Node min_node(Node tree)
{
  assert(tree);
  Node current = tree;
  
  while(current->left) {
    current = current->left;
  }
  return current;
}

Node max_node(Node tree)
{
  assert(tree);
  Node current = tree;
  
  while(current->right) {
    current = current->right;
  }
  return current;
}

void* node_data(Node node)
{
  return node->value;
}
