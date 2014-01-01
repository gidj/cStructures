#ifndef BSTREE_REP_
#define BSTREE_REP_ 

typedef struct Node *Node;

struct Node {
  int key;
  void* value;
  int elementSize;
  Node left, right;
};

extern int  node_key(Node node);
extern void* node_value(Node node);
extern int  node_elementSize(Node node);
extern Node node_left(Node node);
extern Node node_right(Node node);

extern void set_key(Node node, int key);
extern void set_value(Node node, void* value, int elementSize);
extern void set_elementSize(Node node, int size);
extern void set_left(Node node, Node child);
extern void set_right(Node node, Node child);

#endif
