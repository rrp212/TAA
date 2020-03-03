#include <stdio.h>
#include "BinTree.h"

int main()
{
  BinTree<int> t;

  printf("Is empty? %s\n", t.empty()? "Yes":"No");
  t.insert(10); printf("Insert 10\n");
  printf("Is empty? %s\n", t.empty()? "Yes":"No");
  t.insert(5); printf("Insert 5\n");
  t.insert(15); printf("Insert 15\n");
  printf("size %d\n", t.size());
  t.clear(); printf("Clear. Size = %d\n", t.size());
  
  t.insert(10); printf("Insert 10\n");
  t.insert(5); printf("Insert 5\n");
  t.insert(15); printf("Insert 15\n");
  t.insert(15); printf("Insert 15\n");
  printf("size %d\n", t.size());
  t.insert(7); printf("Insert 7\n");
  t.insert(6); printf("Insert 6\n");
  t.remove(5); printf("Remove 5\n");
  printf("size %d\n", t.size());

  return 0;
}
