// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=2733

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6+123;

typedef vector<vector<int>> vvi;

vvi adj(MAX); // lista de adj do grafo
int vis[MAX]; // marca se um vertice ja foi visitado
bool ans; // auxilia na hora de printar a saida

void dfs(int idx, stack<int>& topologicalOrder) {
    if(!ans) return;
    
    vis[idx] = 1;
    
    for(auto e : adj[idx]) {
        if(vis[e] == 0) dfs(e,topologicalOrder);
        else if(vis[e] == 1) ans = false;
    }
    topologicalOrder.push(idx);
    vis[idx] = 2;
}

void solve() {
    int n,m;
    while(cin >> n >> m) {
        if(n == 0 and m == 0) return;

        for(int i = 1; i <= n; i++) {
            adj[i].clear();
        }

        for(int i = 0; i < m; i++) {
            int v1,v2;
            cin >> v1 >> v2;
            adj[v1].push_back(v2);
        }

        stack<int> topologicalOrder;
        memset(vis,0,sizeof(vis));
        ans = true;

        for(int i = 1; i <= n; i++) {
            if(vis[i] == 0) dfs(i,topologicalOrder);
        }

        if(ans) {
            while(!topologicalOrder.empty()) {
                cout << topologicalOrder.top() << "\n";
                topologicalOrder.pop();
            }
        } else {
            cout << "IMPOSSIBLE\n";
        }
        
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}