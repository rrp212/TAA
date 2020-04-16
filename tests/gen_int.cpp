#include <bits/stdc++.h>
using namespace std;

const int NOPS = 11; 
const string OPS[20] = {"empty", "size", "clear", "insert", "remove", "count",
			"lower_bound", "upper_bound", "range_search", "min", "max"};

long long N;
long long lower_lim, upper_lim;
int tot;
int probs[20];

int main()
{
  srand(time(0));
  
  for(int i=0;i<NOPS;i++)
    {
      int p;
      scanf("%d", &p);
      tot+=p;
      probs[i] = tot;
    }

  scanf("%d%d", &lower_lim, &upper_lim);

  int r;
  string op;
  scanf("%lld", &N);
  printf("%lld\n", N);
  for(long long i=0;i<N;i++)
    {
      r = 1+rand()%tot;
      int j;
      for(j=0;j<NOPS;j++)
	if(r<=probs[j])
	  break;
      cout << OPS[j];
      if(3<=j && j<=7)
	cout << " " << (lower_lim+rand()%(upper_lim-lower_lim+1));
      else if(j==8)
	{
	  long long l = lower_lim+rand()%(upper_lim-lower_lim+1);
	  long long r = l+rand()%(upper_lim-l+1);
	  cout << " " << l << " " << r;
	}
      cout << endl;
    }
  
  return 0;
}
