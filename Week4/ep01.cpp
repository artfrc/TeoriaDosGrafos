// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2938

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2123;

vector<vector<int>> adj(MAXN);
vector<vector<int>> inverse(MAXN);
vector<bool> vis(MAXN,false);
stack<int> stk; // guardar a ordem dos vtx

void dfsGraphNormal(int idx) {
    for(auto e : adj[idx]) {
        if(!vis[e]) {
            vis[e] = true;
            dfsGraphNormal(e);
        }
    }
    stk.push(idx);
}

void dfsGraphInv(int idx) {
    for(auto e : inverse[idx]) {
        if(!vis[e]) {
            vis[e] = true;
            dfsGraphInv(e);
        }
    }
}

void solve() {
    int n,m;
    while(cin >> n >> m) {
        if(n == 0 and m == 0) return;

        // Resetando variaveis
        for(int i = 1; i <= n; i++) {
            adj[i].clear();
            inverse[i].clear();
            vis[i] = false;
        }

        // Montando grafo original e inverso
        for(int i = 0; i < m; i++) {
            int x,y,z;
            cin >> x >> y >> z;
            
            adj[x].push_back(y);
            inverse[y].push_back(x);
            if(z != 1) {
                adj[y].push_back(x);
                inverse[x].push_back(y);
            }
        }

        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                vis[i] = true;
                dfsGraphNormal(i);
            }
        }

        int ans = 0;

        for(int i = 1; i <= n; i++) {
            vis[i] = false;
        }

        while(!stk.empty()) {
            int e = stk.top();
            stk.pop();
            if(!vis[e]) {
                vis[e] = true;
                ans++;
                dfsGraphInv(e);
            }
        }

        if(ans > 1) {
            cout << "0\n";
        } else {
            cout << "1\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}