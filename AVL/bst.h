#ifndef BST_H
#define BST_H

// structs da árvore
typedef struct node * link;
struct node {
  link l;
  link r;
  int item;
  int N;
  int id;
};

typedef struct tree {
  link head;
  link z;
} * Tree;

Tree createTree();

// inserção das rotações, busca e inserção da AVL
link right_rotation (Tree t, link h);
link left_rotation (Tree t, link h);
link search (Tree h, int query);
link insert (Tree h, int item);

// impressão da árvore com a ordenação e sem ordenação
void print_out (Tree t, link h);
void print_out_ordination (Tree t, link h);
void print_out_without_ordination (Tree t, link h, int k);

link AVL_insert_right (Tree t,link h, int item);
link AVL_insert (Tree t, int item);

void print_out_AVL (Tree a, char *s);
 
#endif 


