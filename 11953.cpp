#include <iostream>
#include <stdio.h>
using namespace std;

char g[100][100];


int n;
void dfs(int i, int j) {

    // si no existe nada los casos de que no haya nada
    if(i >= n or j >= n or i < 0 or j < 0)
        return;
    //que no hay nada en posicion 
    if(g[i][j] == '.')  
        return;


    g[i][j] = '.';
    dfs(i+1, j);
    dfs(i-1, j);
    dfs(i, j+1);
    dfs(i, j-1);
}
int main() {

    int cases = 0; 
    int i;
    int j;
    int res=0;
    int d;
    cin>>d;
    while(cin>>n){
        for(i = 0; i < n; i++)
            cin>>g[i];
            res=0;
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(g[i][j] == 'x')
                    res++,dfs(i, j);
        cout<<"Case "<<++cases<<": "<<res<<endl;
    }
    return 0;
}