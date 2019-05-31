#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

		int n;
		int data[100];

		void Query(int n,int qa,int qb,int na,int nb){
			if(nb<qa or na>qb)return 0;
			if(na >= qa and nb<=qb) return st[n];
			m=(na+nb)/2;
 	        rl=Query(L(n),qa,qb,na,m);
 	        rr=Query(R(n),qa,qb,m+1,nb);
 	        return min(rl,rr);
 	        Update(int i, int j, int k);
 	    }

 	    void Update(int i, int j, int k){
 	    	for(k=i;k<j;k++){
 	    		Update(k,x);
 	    	}
 	    }

 	    void Get(int *data, int n){
			for (int i=0;i<n; ++i){
        		cout << data[i] << " ";
    		}
		}
		

int main()
{
	int data[10]={1,1,1,1,1,1,1,1,1,1};
		
	int n=10;
    
	
	

}
