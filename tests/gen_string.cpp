#include <bits/stdc++.h>
using namespace std;

const int NOPS = 11; 
const string OPS[20] = {"empty", "size", "clear", "insert", "remove", "count",
			"lower_bound", "upper_bound", "range_search", "min", "max"};

long long N;
int LEN;
int tot;
int probs[20];

string get_string()
{
  char s[LEN+5];
  const char a[40] = "abcdefghijklmnopqrstuvwxyz0123456789";
  for(int i=0;i<LEN;i++)
    s[i] = a[rand()%strlen(a)];
  s[LEN] = 0;
  string S(s);
  return S;
}

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

  scanf("%d", &LEN);

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
	cout << " " << get_string();
      else if(j==8)
	{
	  string l = get_string();
	  string r = get_string();
	  cout << " " << l << " " << r;
	}
      cout << endl;
    }

  return 0;
}
