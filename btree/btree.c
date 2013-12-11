/* A simple binary tree data structure for integers. Any node of the tree
 * can be acted upon like another tree itself. Lower integers are stored on
 * the left, and higher integers are stored on the right. */ 

#include "btree.h"

/* Constructor function create_tree and destructor function destroy_tree 
 * abstract away the details of how we create and destroy the tree. */ 

node* create_tree(int value,
                  node* left,
                  node* right)
{
  node* new_node = (node*) malloc(sizeof(node));
  assert(new_node != NULL);

  set_data(new_node, value);
  set_left(new_node, left);
  set_right(new_node, right);

  return new_node;
}

void destroy_tree(node* tree)
{
  if (tree)
  {
    destroy_tree(left(tree));
    destroy_tree(right(tree));

    free(tree);
  }
}

/* Selector functions. */ 

int data(node* tree)
{
  return tree->data;
}

node* left(node* tree)
{
  return tree->left;
}

node* right(node* tree)
{
  return tree->right;
}

/* Functions to set the values of the tree variables*/ 

void set_data(node* tree, int value)
{
  tree->data = value;
}

void set_left(node* tree, node* child)
{
  tree->left = child;
}

void set_right(node* tree, node* child)
{
  tree->right = child;
}

/* min() and max() functions to return a pointer to the node with the minimum 
 * and maximum values, respectively. */ 

node* min(node* tree)
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

node* max(node* tree)
{
  assert(tree);

  if (right(tree) == NULL) {
    return tree;
  } else {
    return max(right(tree));
  }
}

node* min_parent(node* tree)
{
  assert(tree);
  assert(left(tree));

  if (left(left(tree)) == NULL)
  {
    return tree;
  }
  else
  {
    return min_parent(left(tree));
  }
}

node* max_parent(node* tree)
{
  assert(tree);
  assert(right(tree));

  if (right(right(tree)) == NULL)
  {
    return tree;
  }
  else
  {
    return min_parent(right(tree));
  }
}

/* Printing functions */ 

void print_preorder(node* tree)
{
  if (tree)
  {
    printf("%d\n", data(tree));
    print_preorder(left(tree));
    print_preorder(right(tree));
  }
}

void print_inorder(node* tree)
{
  if (tree)
  {
    print_inorder(left(tree));
    printf("%d\n", data(tree));
    print_inorder(right(tree));
  }
}

void print_postorder(node* tree)
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

node* search_tree(node* tree, int query)
{
  if (!tree)
  {
    return NULL;
  }  

  if (query == data(tree))
  {
    return tree;
  } else if (query < data(tree)) {
    return search_tree(left(tree), query);
  } else {
    return search_tree(right(tree), query);
  }
}

/* Insert function which recursively searches the tree and its children for the
 * value to be inserted; if found, it returns a pointer to the node at which 
 * the value resides in memory; if not found, a new node is created, inserted 
 * at the appropriate place in the tree, and then the function returns a
 * pointer to that node. 
 * In that both search_tree() and insert() both return a reference to the node
 * of interest, they are similar; in the use case that you know you will need 
 * to insert a value into a tree if it isn't found, insert() works better than 
 * searching first, and then inserting if not found. */ 

node* insert(node* tree, int value)
{
  if (value == data(tree))
  {
    return tree;
  }
  else if (value < data(tree))
  {
    if (left(tree) == NULL)
    {
      set_left(tree, create_tree(value, NULL, NULL));
      return left(tree);
    } else {
      return insert(left(tree), value);
    }
  } else {
    if (right(tree) == NULL)
    {
      set_right(tree, create_tree(value, NULL, NULL));
      return right(tree);
    } else {
      return insert(right(tree), value);
    }
  }
}

/* delete_node() is primarily a helper function to delete_data(). There are three 
 * major cases: (1) the node has no children; (2) the node has only one child; 
 * and (3) the node has two children. There is also the unlikely case that the 
 * pointer is simply NULL, and it returns NULL if that is so. */ 

node* delete_node(node* tree)
{
  if (tree == NULL)
  {
    return NULL;
  }
  else if (!left(tree) && !right(tree))
  {
    free(tree);
    return NULL;
  }
  else if (!left(tree))
  {
    node* temp = right(tree);
    free(tree);
    return temp;
  }
  else if (!right(tree))
  {
    node* temp = left(tree);
    free(tree);
    return temp;
  } else
  {

  }
}

/* */ 

node* delete_data(node* tree, int value)
{
  if (tree == NULL)
  {
    return NULL;
  }

  if (data(tree) == value)
  {
    return delete_node(tree);
  }
  else if (value < data(tree))
  {
    set_left(tree, delete_data(left(tree), value));
    return tree;
  } 
  else 
  {
    set_right(tree, delete_data(right(tree), value));
    return tree;
  }
}

