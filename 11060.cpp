#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <queue>

using namespace std;

int main() {
    map<string,int> R;
    vector<int> g[100];
    int indeg[100] = {};
    char cmd[100]; 
    char name[100][100];
    // n numero de bebidas
    int n, m, cases = 0, x, y, tn, i;
    while(scanf("%d", &n) == 1){
        for(i = 0; i < n; i++) {
            scanf("%s", name[i]);
            R[name[i]] = i;
        }
        scanf("%d", &m);
        while(m--) {
            scanf("%s", cmd);
            x = R[cmd];
            scanf("%s", cmd);
            y = R[cmd];
            g[x].push_back(y);
            indeg[y]++;
        }
        priority_queue<int, vector<int>, greater<int> > Q;
        for(i = 0; i < n; i++)
            if(indeg[i] == 0)
                Q.push(i);
        printf("Case #%d: el orden es:", ++cases);
        while(!Q.empty()) {
            tn = Q.top();
            Q.pop();
            for(vector<int>::iterator it = g[tn].begin();
                it != g[tn].end(); it++) {
                indeg[*it]--;
                if(indeg[*it] == 0)
                    Q.push(*it);
            }
            printf(" %s", name[tn]);
        }
cout<<endl;
    }
    return 0;
}