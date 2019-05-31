#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

		int n;
		int data[100];
		int Bit[100];
	
		void AG(int i, int v){
			while(i<=n){
				Bit[i]+=v;
				i+=(i& -i);
			}
		}
		

		int RSQ(int i){
			int s=0;
			while(i>0){
				s +=Bit[i];
				i -= (i& -i);
			}
			return s;
		}
		
		void Update(int i, int v, int n){
			while (i <= n){
        		Bit[i] += v;
        		i += i & (-i);
    		}
		}
		
		void Get(int *data, int n){
			for (int i=0;i<n;i++){
					cout << data[i] << " ";
    		}
    		cout<<endl;
		}
		void GetSum(int *data, int n){
			for(int i=0;i<=n;i++){
				cout<<data[i]<<" ";
			}
			cout<<endl;

		}
		
int main()
{
	int data[10]={5,6,1,8,7,4,11,9,3,0};
	int n=10;

    for (int i=1; i<=n;i++){ 
		Update(i, data[i-1], n);
	}

	Get(data, n);
	GetSum(Bit,n);
  	
	  return 0;
}
