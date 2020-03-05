#include <stdio.h>
#include "Tree.h"
#include "BSNode.h"

int main()
{
  Tree<int, BSNode<int> > t;

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
  t.print();
  t.print(1);
  int a;
  scanf("%d",&a);
  printf("\n\n");
  t.remove(10);
  t.print();
  scanf("%d",&a);
  t.remove(6);
  t.remove(7);
  t.print();
  t.print(1);
  /*
  scanf("%d",&a);
  printf("\n\n");
  t.remove(5);
  t.print();
  printf("\n\n");
  t.remove(20);
  t.print();
  t.print(1);

  printf("%d\n", t.count(14));

  t.clear();
  t.print();
  
  printf("%d\n", t.count(0));*/
  

  return 0;
}
