// https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=183

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50; // numero maximo de vertices do problema

typedef vector<vector<int>> vvi;

map<string,int> mp; // guardar o indice de cada pessoa
vvi adj(MAXN);
vvi inverse(MAXN);
bool vis[MAXN];
stack<int> stk;

string findNameByIdx(int idx) {
    string s;
    for(auto e : mp) {
        if(e.second == idx) {
            s = e.first;
            break;
        }
    }
    return s;
}

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
            cout << ", " << findNameByIdx(e);
            dfsGraphInv(e);
        }
    }
}


void solve() {
    int n,m,t=0;
    bool flag=false;
    
    while(cin >> n >> m) {
        if(n == 0 and m == 0) return;
        if(flag) cout << "\n";
        flag = true;
        cout << "Calling circles for data set " << ++t << ":\n";
        
        // resetar variáveis
        int count = 0;
        mp.clear();
        for(int i = 0; i <= n; i++) {
            adj[i].clear();
            inverse[i].clear();
            vis[i] = false;
        }

        for(int i = 0; i  < m; i++) {
            string name1, name2;
            cin >> name1 >> name2;

            if(mp[name1] == 0) {
                mp[name1] = ++count;
            }

            if(mp[name2] == 0) {
                mp[name2] = ++count;
            }

            int idxName1 = mp[name1], idxName2 = mp[name2];
            
            adj[idxName1].push_back(idxName2);
            inverse[idxName2].push_back(idxName1);
        }

        memset(vis,false,sizeof(vis));

        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                vis[i] = true;
                dfsGraphNormal(i);
            }
        }

        memset(vis,false,sizeof(vis));

        while(!stk.empty()) {
            auto e = stk.top();
            stk.pop();
            if(!vis[e]) {
                vis[e] = true;
                cout << findNameByIdx(e);
                dfsGraphInv(e);
                cout << "\n";
            }
        }

    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();
}