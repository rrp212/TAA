// int   or   std::string
#define MYTYPE std::string
// 0     or   "x"
#define DEFAULT "x"
#define INPUT(x) std::cin >> x
#define PRINT(x) std::cout << x << std::endl
#define SHOW false
#define DEBUG (true && SHOW)

#include <ctime>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../lib/Tree.h"
#include "../lib/BSNode.h"
#include "../lib/AVLNode.h"
#include "../lib/SplayNode.h"
#include "../lib/TreapNode.h"
#include "../lib/SkipList.h"
#include "../lib/STL.h"

long long N;
std::vector<std::string> VC;
std::vector<std::pair<MYTYPE,MYTYPE > > VV;

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


  
  // >>>>>>>>>>>> INPUT <<<<<<<<<<<<
  
  std::cin >> N;
  std::string com;
  MYTYPE v1,v2;
  for(long long i=0;i<N;i++)
    {
      v1 = v2 = DEFAULT;
      std::cin >> com;
      VC.push_back(com);
      if(com=="insert"||com=="remove"||com=="count"||
	 com=="lower_bound"||com=="upper_bound"||com=="range_search")
	INPUT(v1);
      if(com=="range_search")
	INPUT(v2);
      VV.push_back(std::make_pair(v1,v2));
    }


  
  // >>>>>>>>>>>> WORK <<<<<<<<<<<<
  
  clock_t start = clock();
  for(long long i=0;i<N;i++)
    {
      com = VC[i];
      if(com == "empty")
	{
	  bool b = S->empty();
	  if(SHOW) printf("%s\n", b? "T":"F");
	}
      else if(com == "size")
	{
	  long long s = S->size();
	  if(SHOW) printf("%lld\n", s);
	}
      else if(com == "clear")
	{
	  S->clear();
	  if(DEBUG) printf("clear\n");
	}
      else if(com == "insert")
	{
	  S->insert(VV[i].first);
	  if(DEBUG) std::cout << "insert ";
	  if(DEBUG) PRINT(VV[i].first);
	}
      else if(com == "remove")
	{
	  S->remove(VV[i].first);
	  if(DEBUG) std::cout << "remove ";
	  if(DEBUG) PRINT(VV[i].first);
	}
      else if(com == "count")
	{
	  bool b = S->count(VV[i].first);
	  if(SHOW) std::cout << (b? "T":"F") << std::endl;
	}
      else if(com == "lower_bound")
	{
	  auto ans = S->lower_bound(VV[i].first);
	  if(SHOW)
	    {
	      if(ans.second)
		PRINT(ans.first);
	      else
		printf("F\n");
	    }
	}
      else if(com == "upper_bound")
	{
	  auto ans = S->upper_bound(VV[i].first);
	  if(SHOW)
	    {
	      if(ans.second)
		PRINT(ans.first);
	      else
		printf("F\n");
	    }
	}
      else if(com == "range_search")
	{
	  bool b = S->range_search(VV[i].first,VV[i].second);
	  if(SHOW) std::cout << (b? "T":"F") << std::endl;
	}
      else if(com == "min")
	{
	  auto ans = S->min();
	  if(SHOW)
	    {
	      if(ans.second)
		PRINT(ans.first);
	      else
		printf("F\n");
	    }
	}
      else if(com == "max")
	{
	  auto ans = S->max();
	  if(SHOW)
	    {
	      if(ans.second)
		PRINT(ans.first);
	      else
		printf("F\n");
	    }
	}
      else
	printf("command not defined\n");
    }

  printf("%lf\n", double(clock() - start) / CLOCKS_PER_SEC);

  return 0;
}
