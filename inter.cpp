// int   or   std::string
#define MYTYPE int
// 0     or   "x"
#define DEFAULT 0
#define INPUT(x) std::cin >> x
#define PRINT(x) std::cout << x << std::endl

#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "lib/Tree.h"
#include "lib/BSNode.h"
#include "lib/AVLNode.h"
#include "lib/SplayNode.h"
#include "lib/TreapNode.h"
#include "lib/SkipList.h"
#include "lib/STL.h"

long long N;

int main()
{
  // >>>>>>>>>>>> TYPE <<<<<<<<<<<<
  
  std::string impl = "None";
  std::cin >> impl;

  std::string node = "None";
  if(impl=="Tree")
    std::cin >> node;
  
  Set<MYTYPE > *S;
  Tree<MYTYPE, BSNode<MYTYPE > >    tbs;
  Tree<MYTYPE, AVLNode<MYTYPE > >   tavl;
  Tree<MYTYPE, SplayNode<MYTYPE > > tspl;
  Tree<MYTYPE, TreapNode<MYTYPE > > ttrp;
  SkipList<MYTYPE > skip;
  STL<MYTYPE > base;

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


  
  // >>>>>>>>>>>> WORK <<<<<<<<<<<<
  
  std::cin >> N;
  std::string com;
  MYTYPE v1,v2;
  for(long long i=0;i<N;i++)
    {
      v1 = v2 = DEFAULT;
      std::cin >> com;
      if(com=="insert"||com=="remove"||com=="count"||
	 com=="lower_bound"||com=="upper_bound"||com=="range_search")
	INPUT(v1);
      if(com=="range_search")
	INPUT(v2);
      
      if(com == "empty")
	{
	  bool b = S->empty();
	  printf("%s\n", b? "T":"F");
	}
      else if(com == "size")
	{
	  long long s = S->size();
	  printf("%lld\n", s);
	}
      else if(com == "clear")
	{
	  S->clear();
	  printf("clear\n");
	}
      else if(com == "insert")
	{
	  S->insert(v1);
	  std::cout << "insert ";
	  PRINT(v1);
	}
      else if(com == "remove")
	{
	  S->remove(v1);
	  std::cout << "remove ";
	  PRINT(v1);
	}
      else if(com == "count")
	{
	  bool b = S->count(v1);
	  std::cout << (b? "T":"F") << std::endl;
	}
      else if(com == "lower_bound")
	{
	  auto ans = S->lower_bound(v1);
	  if(ans.second)
	    PRINT(ans.first);
	  else
	    printf("F\n");
	}
      else if(com == "upper_bound")
	{
	  auto ans = S->upper_bound(v1);
	  if(ans.second)
	    PRINT(ans.first);
	  else
	    printf("F\n");
	}
      else if(com == "range_search")
	{
	  bool b = S->range_search(v1,v2);
	  std::cout << (b? "T":"F") << std::endl;
	}
      else if(com == "min")
	{
	  auto ans = S->min();
	  if(ans.second)
	    PRINT(ans.first);
	  else
	    printf("F\n");
	}
      else if(com == "max")
	{
	  auto ans = S->max();
	  if(ans.second)
	    PRINT(ans.first);
	  else
	    printf("F\n");
	}
      else
	printf("command not defined\n");
    }

  return 0;
}
