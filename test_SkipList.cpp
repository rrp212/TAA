#include <iostream>
#include <string>

#include "SkipList.h"

int main()
{
  SkipList<int> t;
  std::string command;

  srand(time(0));
  
  while(1)
    {
      std::cin >> command;
      if(command == "empty")
	{
	  printf("t is%s empty\n", t.empty()? " ":" not");
	}
      else if(command == "size")
	{
	  printf("size: %d\n", t.size());
	}
      else if(command == "clear")
	{
	  t.clear().print();
	}
      else if(command == "insert")
	{
	  int a; std::cin >> a;
	  t.insert(a).print();
	}
      else if(command == "remove")
	{
	  int a; std::cin >> a;
	  t.remove(a).print();
	}
      else if(command == "count")
	{
	  int a; std::cin >> a;
	  printf("%d%s found\n", a, t.count(a)? "":" not");
	}
      else if(command == "lower_bound")
	{
	  int a; std::cin >> a;
	  std::pair<int,bool> b = t.lower_bound(a);
	  if(b.second)
	    printf("%d\n", b.first);
	  else
	    printf("Lower bound of %d not found\n", a);
	}
      else if(command == "upper_bound")
	{
	  int a; std::cin >> a;
	  std::pair<int,bool> b = t.upper_bound(a);
	  if(b.second)
	    printf("%d\n", b.first);
	  else
	    printf("Upper bound of %d not found\n", a);
	}
      else if(command == "range_search")
	{
	  int a, b; std::cin >> a >> b;
	  printf("Value in range%s found\n", t.range_search(a,b)? "":" not");
	}
      else if(command == "min")
	{
	  if(t.min().second)
	    printf("min: %d\n", t.min().first);
	  else
	    printf("empty\n");
	}
      else if(command == "max")
	{
	  if(t.max().second)
	    printf("max: %d\n", t.max().first);
	  else
	    printf("empty\n");
	}
      else if(command == "print")
	{
	  int a; std::cin >> a;
	  t.print(a);
	}
      else
	printf("command not defined\n");
    }

  return 0;
}
