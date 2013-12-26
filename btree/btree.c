/* A simple binary tree data structure for integers. Any node of the tree
 * can be acted upon like another tree itself. Lower integers are stored on
 * the left, and higher integers are stored on the right. */ 

#include "btree.h"
#include <stdlib.h>

struct node {
    int key;
    void* value;
    struct node *left;
    struct node *right;
};

/* Constructor function create_tree and destructor function destroy_tree 
 * abstract away the details of how we create and destroy the tree. */ 

node create_tree(int key, 
                 void* value,
                 node left,
                 node right)
{
  node new_node = (node) malloc(sizeof(node));
  assert(new_node);

  key_set(new_node, key);
  value_set(new_node, value);
  left_set(new_node, left);
  right_set(new_node, right);

  return new_node;
}

void destroy_tree(node tree)
{
  if (tree)
  {
    destroy_tree(left(tree));
    destroy_tree(right(tree));

    free(tree);
  }
}

/* Selector functions. */ 

int key(node tree)
{
  return tree->key;
}

node left(node tree)
{
  return tree->left;
}

node right(node tree)
{
  return tree->right;
}

/* Functions to set the values of the tree variables*/ 

void key_set(node tree, int key)
{
  tree->key = key;
}

void value_set(node tree, void* value)
{
  assert(tree && value);
  if (sizeof(tree->value) != sizeof(*value))
  {
    tree->value = realloc(tree->value, sizeof(*value));
  }
  memcpy(tree->value, value, sizeof(*value));
}

void left_set(node tree, node child)
{
  tree->left = child;
}

void right_set(node tree, node child)
{
  tree->right = child;
}

/* min() and max() functions to return a pointer to the node with the minimum 
 * and maximum values, respectively. */ 

node min(node tree)
{
  if (tree == NULL)
  {
     /* ToDo: currently this function returns a NULL pointer if the tree is empty;
      * later, create an error handling routine to return an error instead to signal
      * that there are no elementes in the tree. */ 
    return tree;
  } else if (left(tree) == NULL) {
    return tree;
  } else {
    return min(left(tree));
  }
}

node max(node tree)
{
  assert(tree);

  if (right(tree) == NULL) {
    return tree;
  } else {
    return max(right(tree));
  }
}

/* Printing functions */ 

void print_preorder(node tree)
{
  if (tree)
  {
    printf("%d\n", value(tree));
    print_preorder(left(tree));
    print_preorder(right(tree));
  }
}

void print_inorder(node tree)
{
  if (tree)
  {
    print_inorder(left(tree));
    printf("%d\n", data(tree));
    print_inorder(right(tree));
  }
}

void print_postorder(node tree)
{
  if (tree)
  {
    print_postorder(left(tree));
    print_postorder(right(tree));
    printf("%d\n", data(tree));
  }
}

/* Search function that returns the node containing the given object of 
 * interest, or NULL if it cannot be found. */ 

node search_tree(node tree, int query)
{
  if (!tree)
  {
    return NULL;
  }  

  if (query == key(tree))
  {
    return tree;
  } 
  else if (query < data(tree)) 
  {
    return search_tree(left(tree), query);
  } 
  else 
  {
    return search_tree(right(tree), query);
  }
}

/* insert() takes a pointer to a pointer that points to a tree, and a value to
 * insert into that tree. It recursively checks to see if the value exists; if 
 * so, the function exits and nothing is done. If not and it reaches a NULL 
 * leaf, a new node is created with the provided value and it is inserted in
 * place of the NULL node. */ 

void insert(node *tree, int key, void* value)
{
  if ((*tree) == NULL)
  {
    (*tree) = create_tree(key, value, NULL, NULL);
  }
  else if ((*tree)->key > key)
  {
    tree = &((*tree)->left);
    insert(tree, key, value);
  } 
  else if ((*tree)->key < key) 
  {
    tree = &((*tree)->right);
    insert(tree, key, value);
  }
  else 
  {
/* This is the case where the value at the node equals the value provided to 
 * the function
 * TODO: Add error codes via an integer type. */ 
  }
}

/* delete_node() is primarily a helper function to delete_data(). There are three 
 * major cases: (1) the node has no children; (2) the node has only one child; 
 * and (3) the node has two children. There is also the unlikely case that the 
 * pointer is simply NULL. */ 

void delete_node(node* n)
{
  if (n == NULL)
  {
  }
  else if (!left(*n) && !right(*n))
  {
    node temp = *n;
    (*n) = NULL;
    free(temp->value);
    free(temp);
  }
  else if (!left(*n))
  {
    node temp = *n;
    (*n) = right(*n);
    free(temp->value);
    free(temp);
  }
  else if (!right(*n))
  {
    node temp = *n;
    (*n) = left(*n);
    free(temp->value);
    free(temp);
  } else
  {

/* The final case, where there are two children to the node to be deleted. 
 * We find the successor, which is simply the node with the minimum key value
 * on the right side of the tree. If that success is ALSO the right child of 
 * tree, then it is a simple case of simply 'moving' the right child to take
 * the place of the head of tree. If the successor is in the right subtree but
 * is NOT the right child, the data from successor is moved into the head of 
 * tree, and then successor's own right child takes its place. This is done
 * via a recursive calle to the delete_node() function, as it nicely fits one
 * of the above cases. */ 

    node successor = min(right(*n));

    if (successor == right(*n))
    {
      key_set(*n, key(successor));
      value_set(*n, value(successor));
      right_set(*n, right(successor));
      free(successor->value);
      free(successor);
    }
    else
    {
      key_set(*n, key(successor));
      value_set(*n, value(successor));
      delete_node(&successor);
    }
  }
}

/* */ 

void delete_value(node tree, int key)
{
  node element = search_tree(tree, key);
  delete_node(&element);
}

