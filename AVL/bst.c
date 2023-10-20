#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// atribuição de valores
int id = 0;
link new (int item, link l, link r) {
  link t = malloc(sizeof(struct node));
  t->item = item;
  t->l = l;
  t->r = r;
  t->N = 1;
  t->id = id++;
  return t;
}
Tree createTree(){
  Tree t = malloc (sizeof (struct tree));
  t->z = malloc (sizeof(struct node));
  t->head = t->z;
  t->z->l = t->z;
  t->z->N = 0;
  t->z->r = t->z;
  return t;
}

link right_rotation (Tree t, link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  return x;
}

link left_rotation (Tree t, link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  return x;
}

link right_search(Tree t, link h, int query) {
  if (h == t->z) {
    return NULL;
  }
  if(h->item == query) 
    return h;
  if (h->item >= query) 
    return right_search(t, h->l, query);
  return right_search(t, h->r, query);
} 


link search (Tree t, int query){
   return right_search(t, t->head, query);
}

link right_insertion (Tree t, link h, link n) {
  if (h == t->z) {
    return  n;
  }

  if(h->item >= n->item)
    h->l = right_insertion(t, h->l, n);
  else 
    h->r = right_insertion(t, h->r, n);
  (h->N)++;
  return h;
}

link insert (Tree t, int item){
  if(t->head == t->z) {
    return (t->head =new(item, t->z, t->z));
  }
  return right_insertion(t, t->head, new(item, t->z, t->z));
}

// funções
void print_out (Tree t, link h){
  if(h == t->z) return;
  print_out (t, h->l);
  printf("<chave: %d N: %d>", h->item, h->N); 
  print_out (t, h->r);
}

void print_out_ordination (Tree t, link h){
  if(h == t->z) return;
  print_out_ordination (t, h->l);
  print_out_ordination (t, h->r);
  printf("<chave: %d N: %d>", h->item, h->N); 
}
void print_out_without_ordination (Tree t, link h, int k) {
  if(h == t->z) return;
  int i; //mudanca
  for(i = 0; i <= k; i++)
    printf (" . ");
  printf("<chave: %d N: %d>\n", h->item, h->N); 
  print_out_without_ordination (t, h->l, k + 1); 
  print_out_without_ordination (t, h->r, k + 1);
}

void printnode (char  *x, int h) {
    int i;
    for(i = 0; i < h; i++)
        printf("\t");
    printf("%s\n", x);
}

int c = 0;

void right_print_out(Tree a, link t){
    char s[255];
    if(t==a->z) { return;}
    right_print_out(a,t->r);
    printf ("%d [ label = \"<f0>| <f1> %d (%d) | <f2>\" ]\n", t->id, t->item, t->N);
    if(t->l != a->z){
        printf("%d:f0->%d:f1;\n", t->id, t->l->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f0->z%d;\n", t->id, c);
        c++;
    }
    if(t->r != a->z){
        printf("%d:f2->%d:f1;\n", t->id, t->r->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f2->z%d;\n", t->id, c );
        c++;
    }
    right_print_out(a,t->l);
}
void print_out_AVL(Tree a, char *s) {
    c = 0;
    printf("digraph %s {\n", s);
    printf ("node [shape=record,style=rounded, height=.1]\n");
    right_print_out(a, a->head);
    printf("}\n");
}
void print_out_node(Tree a, link h, char *s) {
  c = 0;
  printf("digraph  {\n" );
  printf ("name [label = \"%s\",shape=plaintext]\n", s);
  printf ("node [shape=record,style=rounded, height=.1]\n");
  right_print_out(a, h);
  printf("}\n");
}

link AVLright_insertion(Tree t, link h, int item){
    if (h == t->z) {
    return new(item, t->z, t->z);
  }

// definição da prioridade de inserção
  if (item < h->item) {
    h->l = AVLright_insertion(t, h->l, item);
  } else {
    h->r = AVLright_insertion(t, h->r, item);
  }

// altura da árvore
  h->N = 1 + ((h->l->N > h->r->N) ? h->l->N : h->r->N);

  // equilibrar nós
  int balance = h->l->N - h->r->N;

  // rotação de árvore
  if (balance > 1) {
    if (item < h->l->item) {
      // rotação direita
      return right_rotation(t, h);
    } else {
      // rotação dupla esquerda-direita
      h->l = left_rotation(t, h->l);
      return right_rotation(t, h);
    }
  } else if (balance < -1) {
    if (item > h->r->item) {
      // rotação esquerda
      return left_rotation(t, h);
    } else {
      // rotação dupla direita-esquerda
      h->r = right_rotation(t, h->r);
      return left_rotation(t, h);
    }
  }
  return h;
}

link AVL_insert(Tree t, int item) {
  t->head = AVLright_insertion(t, t->head, item);
  return t->head;
}