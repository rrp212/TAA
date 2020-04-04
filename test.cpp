#include <iostream>
#include <string>

#include "lib/Tree.h"
#include "lib/BSNode.h"
#include "lib/AVLNode.h"
#include "lib/SplayNode.h"
#include "lib/TreapNode.h"
#include "lib/SkipList.h"
#include "lib/STL.h"


int main()
{
  srand(42);
  std::string impl = "None";
  // Uncomment for interactive testing
  //
  //  while(impl!="Tree" && impl!="SkipList" && impl!="STL")
  //    {
  //      printf("Choose set implementation (Tree, SkipList, STL)\n");
      std::cin >> impl;
  //    }

  std::string node = "None";
  if(impl=="Tree")
    // Uncomment for interactive testing
    //
    //    while(node!="BS" && node!="AVL" && node!="Splay" && node!="Treap")
    //      {
    //	printf("Choose node implementation (BS, AVL, Splay, Treap)\n");
	std::cin >> node;
    //      }
  
  Set<int> *S;
  Tree<int, BSNode<int> >    tbs;
  Tree<int, AVLNode<int> >   tavl;
  Tree<int, SplayNode<int> > tspl;
  Tree<int, TreapNode<int> > ttrp;
  SkipList<int> skip;
  STL<int> base;

  if(impl=="Tree" && node=="BS")
    S = &tbs;
  else if(impl=="Tree" && node=="AVL")
    S = &tavl;
  else if(impl=="Tree" && node=="Splay")
    S = &tspl;
  else if(impl=="Tree" && node=="Treap")
    S = &ttrp;
  else if(impl=="SkipList")
    S = &skip;
  else
    S = &base;
  
  std::string command;
  while(1)
    {
      std::cin >> command;
      if(command == "empty")
	{
	  printf("%s\n", S->empty()? "true":"false");
	}
      else if(command == "size")
	{
	  printf("%d\n", S->size());
	}
      else if(command == "clear")
	{
	  S->clear();
	  printf("clear\n");
	}
      else if(command == "insert")
	{
	  int v; std::cin >> v;
	  S->insert(v);
	  printf("insert %d\n", v);
	}
      else if(command == "remove")
	{
	  int v; std::cin >> v;
	  S->remove(v);
	  printf("remove %d\n", v);
	}
      else if(command == "count")
	{
	  int v; std::cin >> v;
	  printf("%s\n", S->count(v)? "true":"false");
	}
      else if(command == "lower_bound")
	{
	  int v; std::cin >> v;
	  auto ans = S->lower_bound(v);
	  if(ans.second)
	    printf("%d\n", ans.first);
	  else
	    printf("false\n");
	}
      else if(command == "upper_bound")
	{
	  int v; std::cin >> v;
	  auto ans = S->upper_bound(v);
	  if(ans.second)
	    printf("%d\n", ans.first);
	  else
	    printf("false\n");
	}
      else if(command == "range_search")
	{
	  int l,r; std::cin >> l >> r;
	  printf("%s\n", S->range_search(l,r)? "true":"false");
	}
      else if(command == "min")
	{
	  auto ans = S->min();
	  if(ans.second)
	    printf("%d\n", ans.first);
	  else
	    printf("false\n");
	}
      else if(command == "max")
	{
	  auto ans = S->max();
	  if(ans.second)
	    printf("%d\n", ans.first);
	  else
	    printf("false\n");
	}
      else if(command == "print")
	{
	  int a; std::cin >> a;
	  S->print(a);
	}
      else if(command == "quit")
	break;
      else
	printf("command not defined\n");
    }

  return 0;
}
