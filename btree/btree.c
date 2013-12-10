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

  set_value(new_node, value);
  set_left(new_node, left);
  set_right(new_node, right);

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

/* Selector functions. */ 

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

/* Functions to set the values of the tree variables*/ 

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

/* Printing functions */ 

void print_preorder(node* tree)
{
  if (tree)
  {
    printf("%d\n", get_value(tree));
    print_preorder(get_left(tree));
    print_preorder(get_right(tree));
  }
}

void print_inorder(node* tree)
{
  if (tree)
  {
    print_inorder(get_left(tree));
    printf("%d\n", get_value(tree));
    print_inorder(get_right(tree));
  }
}

void print_postorder(node* tree)
{
  if (tree)
  {
    print_postorder(get_left(tree));
    print_postorder(get_right(tree));
    printf("%d\n", get_value(tree));
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

  if (query == get_value(tree))
  {
    return tree;
  } else if (query < get_value(tree)) {
    return search_tree(get_left(tree), query);
  } else {
    return search_tree(get_right(tree), query);
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
  if (value == get_value(tree))
  {
    return tree;
  }
  else if (value < get_value(tree))
  {
    if (get_left(tree) == NULL)
    {
      set_left(tree, create_tree(value, NULL, NULL));
      return get_left(tree);
    } else {
      return insert(get_left(tree), value);
    }
  } else {
    if (get_right(tree) == NULL)
    {
      set_right(tree, create_tree(value, NULL, NULL));
      return get_right(tree);
    } else {
      return insert(get_right(tree), value);
    }
  }
}


