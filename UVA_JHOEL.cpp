#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

#define N 200001

int n;
int data[N];
int result[N];

void Update(int i, int v, int n)
{
	while (i <= n)
	{
       	result[i] += v;
       	i += i & (-i);
  	}		
}
	
int Rsq(int i)
{
	int s=0;
	while(i>0)
	{
		s += result[i];
		i -= (i& -i);
	}
	return s;
}
				
void Get(int *data, int n)
{
	for (int i=0; i<=n; ++i)
	{
      	cout << data[i] << " ";
   	}
}
		
//};

int main()
{
	int cas;
	int x;
	int y;
	char let[3];
	
	scanf("%d", &n);
	while(n>0)
	{
	 	for (int i = 1; i <= n; i++)
		{ 
			scanf("%d", data + i);
			Update(i, data[i], n);
		}
		printf("Case %d:\n", cas++);
		
		while(scanf("%s", let), let[0] != 'E')
		{
			scanf("%d %d", &x, &y);
			if(let[0] == 'M')
			{
				printf("%d\n", Rsq(y) - Rsq(x - 1));
			}
			else 
			{
				Update(x, y - data[x],n);
				data[x] = y;
			}
		}
	}
	
	return 0;
}
