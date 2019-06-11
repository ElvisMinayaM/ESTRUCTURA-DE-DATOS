#include <iostream>
#include <string>

using namespace std;
#define numb 100001

int a[numb];
int st[4*numb];
int max=1000000000;
				
int Query(int n, int qa, int qb, int na, int nb)
{		
	if(qa>nb || qa>qb || na>qb)
		return max;
			
	if(qa>=na && nb>=qb)
		return st[n];
		
	int m=(qa+qb)/2;
		
	int RL=Query(n+n+1, qa, m, na, nb);
	int RR=Query(n+n+2, m+1, qb, na,nb);
		
	return min(RL, RR);
}
	
void Build(int i, int l, int r)
{
	if(l>r)
	{
		return ;
	}
	      
	if(l==r)
	{
	    st[i]=a[l];
	    return;
	}
	int m=(l+r)/2;
	
	Build(i+i+1, l, m);
	Build(i+i+2, m+1, r);
	st[i]=min(st[i+1+i], st[i+i+2]);	
}
	
int main()
{	
	int n;
	int q;
	int l;
	int r;
	scanf("%d", &n); /*Posibles resultados no deseados al leer un solo caracter*/
	
	for(int i=1; i<=n; ++i)
	   scanf("%ld",a+i);
	    
	Build(1,1,n);
	scanf("%d", &q);
	while(q--)
	{
	    scanf("%d%d", &l, &r);
    	printf("%ld\n",Query(1,1,n,l+1,r+1));
	}
	return 0;
}
