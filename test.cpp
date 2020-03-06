#include <stdio.h>
#include "Tree.h"
#include "BSNode.h"

#define BREAK scanf("%d", &a);printf("\n\n");

int main()
{
  Tree<int, BSNode<int> > t;
  int a;

  t.insert(20);
  t.insert(10);
  t.insert(30);
  t.insert(5);
  t.print(2);
  BREAK;
  t.clear();
  t.print();
  BREAK;
  t.insert(20);
  t.insert(10);
  t.insert(30);
  t.insert(5);
  t.insert(15);
  t.insert(35);
  t.insert(25);
  t.insert(1);
  t.insert(12);
  t.insert(17);
  t.insert(7);
  t.insert(6);
  t.insert(9);
  t.print(2);
  BREAK;
  t.remove(10).insert(10);
  t.print();

  return 0;
}
