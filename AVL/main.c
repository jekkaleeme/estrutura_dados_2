#include <stdio.h>
#include "bst.h"
#include "bst.c"

int main () {
  Tree t = createTree();
  link x;

// inserção dos valores
  insert(t, 99);
  insert(t, 88);
  insert(t, 77);
  insert(t, 66);

// chamada da função AVL
  AVL_insert(t, 55);
  
// impreção de todos os valores somente uma vez 
  print_out_AVL(t, "oi");

  return 0;
}