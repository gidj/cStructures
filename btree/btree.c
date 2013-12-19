/* A simple binary tree data structure for integers. Any node of the tree
 * can be acted upon like another tree itself. Lower integers are stored on
 * the left, and higher integers are stored on the right. */ 

#include "btree.h"

struct node {
    struct node *left;
    struct node *right;
    int data;
};

/* Constructor function create_tree and destructor function destroy_tree 
 * abstract away the details of how we create and destroy the tree. */ 

node create_tree(int value,
                  node left,
                  node right)
{
  node new_node = (node) malloc(sizeof(node));
  assert(new_node != NULL);

  set_data(new_node, value);
  set_left(new_node, left);
  set_right(new_node, right);

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

int data(node tree)
{
  return tree->data;
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

void set_data(node tree, int value)
{
  tree->data = value;
}

void set_left(node tree, node child)
{
  tree->left = child;
}

void set_right(node tree, node child)
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
    printf("%d\n", data(tree));
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

  if (query == data(tree))
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

void insert(node* tree, int value)
{
  if ((*tree) == NULL)
  {
    (*tree) = create_tree(value, NULL, NULL);
  }
  else if (value < data(*tree))
  {
    *tree = left(*tree);
    insert(tree, value);
  } 
  else if (value > data(*tree)) 
  {
    *tree = right(*tree);
    insert(tree, value);
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

void delete_node(node* tree)
{
  if (tree == NULL)
  {
  }
  else if (!left(*tree) && !right(*tree))
  {
    node temp = *tree;
    (*tree) = NULL;
    free(temp);
  }
  else if (!left(*tree))
  {
    node temp = *tree;
    (*tree) = right(*tree);
    free(temp);
  }
  else if (!right(*tree))
  {
    node temp = *tree;
    (*tree) = left(*tree);
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

    node successor = min(right(*tree));

    if (successor == right(*tree))
    {
      set_data(*tree, data(successor));
      set_right(*tree, right(successor));
      free(successor);
    }
    else
    {
      set_data(*tree, data(successor));
      delete_node(&successor);
    }
  }
}

/* */ 

void delete_data(node tree, int value)
{
  node element = search_tree(tree, value);
  delete_node(&element);
}

