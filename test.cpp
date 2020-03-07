#include <iostream>
#include <string>

#include "Tree.h"
#include "BSNode.h"

int main()
{
  Tree<int, BSNode<int> > t;
  std::string command;
  
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
	  printf("not done yet\n");
	}
      else if(command == "upper_bound")
	{
	  printf("not done yet\n");
	}
      else if(command == "range_search")
	{
	  printf("not done yet\n");
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
      else if(command == "rotate_left")
	{
	  int a; std::cin >> a;
	  if(t.root->value == a)
	    t.root = t.root->rotate_left();
	  else
	    t.root->insert(a)->rotate_left();
	  t.print();
	}
      else if(command == "rotate_right")
	{
	  int a; std::cin >> a;
	  if(t.root->value == a)
	    t.root = t.root->rotate_right();
	  else
	    t.root->insert(a)->rotate_right();
	  t.print();
	}
      else
	printf("command not defined\n");
    }

  return 0;
}
