#include "BSTree.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Node {
  int key;
  void* value;
  int elementSize;
  Node left, right;
};

/* tree_create() gives us a tree, preppted with the given parameters. tree_destroy
 * recursively frees all nodes and all data associated with the nodes. */ 

Node tree_create(int key, void* value, int elementSize, Node left, Node right)
{
  assert(value);
  assert(elementSize > 0);
  
  Node node = malloc(sizeof(*node));
  assert(node);

  set_key(node, key);
  set_value(node, value, elementSize);
  set_elementSize(node, elementSize);
  set_left(node, left);
  set_right(node, right);

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

/* min_value() and max_value() return pointers to the data being stored in the
 * nodes with the minimum and maximum key values, repectively. It is up to the
 * programmer to dereference the pointer through an appropriate cast. */ 

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

/* Given a key to search for in the given tree, tree_search returns a pointer 
 * to the value associated with that key, or NULL if the key is not in the
 * tree. */ 

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

/* tree_insert() searches until it either finds the given key in the tree and
 * replaces the value of that node with the given value, or reaches a leaf and
 * creates a new node with the given key and value. */ 

void tree_insert(Node tree, int key, void* value, int elementSize)
{
  assert(tree);
  Node current = tree;

  if (key == current->key)
  {
    set_value(current, value, elementSize);
    set_elementSize(current, elementSize);
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
      set_left(current, tree_create(key, value, elementSize, NULL, NULL));
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
      set_right(current, tree_create(key, value, elementSize, NULL, NULL));
      return;
    }
  }
}

/* tree_delete() takes a pointer to a tree type and a key to search for; if the
 * key is found in the tree, that node is removed from the tree. If the key is 
 * not found, nothing happens. */ 

void tree_delete(Node *tree, int key)
{
  if (*tree)
  {
    if (key == (*tree)->key)
    {
      node_delete(tree);
    }
    else if (key < (*tree)->key)
    {
      tree_delete(&(*tree)->left, key);
    }
    else if (key > (*tree)->key)
    {
      tree_delete(&(*tree)->right, key);
    }
  }
  return;
}

/* node_delete() does the heavy lifting for tree_delete. It takes a pointer
 * to a node object and then determines which of three cases the node falls
 * into:
 * (1) No children; deletion is straightforward. 
 * (2) One child; the child node simply replaces the node to be deleted.
 * (3) Two children; the node to be deleted is replaced by its successor.*/

void node_delete(Node *node)
{
  if (*node)
  {
    if (!node_left(*node) && !node_right(*node))
    {
      Node tmp = *node;
      *node = NULL;
      free(node_value(tmp));
      free(tmp);
      return;
    }
    else if (!node_left(*node))
    {
      Node tmp = *node;
      *node = node_right(*node);
      free(tmp->value);
      free(tmp);
      return;
    }
    else if (!node_right(*node))
    {
      Node tmp = *node;
      *node = node_left(*node);
      free(tmp->value);
      free(tmp);
      return;
    }
    else
    {
      Node successor = node_right((*node));
      Node successorParent = (*node);

      while(successor->left) {
        successorParent = successor;
        successor = node_left(successor);
      }

      if (node_right(*node) == successor)
      {
        Node temp = *node;
        set_left(successor, node_left(*node));
        *node = successor;

        free(temp->value);
        free(temp);
        return;
      }
      else
      {
        set_left(successorParent, node_right(successor));
        set_left(successor, node_left(*node));
        set_right(successor, node_right(*node));

        Node temp = *node;
        *node = successor;
        
        free(temp->value);
        free(temp);

        return;
      }
    }
  }
}

/* Helper functions that get and set values in Node types.*/ 

int node_key(Node node)
{ return node->key; }

void* node_value(Node node)
{ return node->value; }

int  node_elementSize(Node node)
{ return node->elementSize; }

Node node_left(Node node)
{ return node->left; }

Node node_right(Node node)
{ return node->right; }

void set_key(Node node, int key)
{ node->key = key; }

void set_value(Node node, void* value, int elementSize)
{ 
  void* tmp = realloc(node->value, elementSize);

  if (tmp) 
  { 
    node->value = tmp; 
  }
  else 
  { 
    printf("Memory allocation failed. Exiting...\n");
    exit(EXIT_FAILURE); 
  }

  memcpy(node->value, value, elementSize);
  set_elementSize(node, elementSize);
}

void set_elementSize(Node node, int size)
{ node->elementSize = size; }

void set_left(Node node, Node child)
{ node->left = child; }

void set_right(Node node, Node child)
{ node->right = child; }

Node* min_node(Node* tree)
{
  assert(tree);
  assert(*tree);
  
  while((*tree)->left) {
    tree = &(*tree)->left;
  }
  return tree;
}

Node* max_node(Node* tree)
{
  assert(tree);
  assert(*tree);

  while((*tree)->right) {
    tree = &(*tree)->right;
  }
  return tree;
}

