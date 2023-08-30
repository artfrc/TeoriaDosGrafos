// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2938

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2123; // numero maximo de vertices que pode ter no problema

vector<vector<int>> adj(MAXN); // lista de adj do grafo original
vector<vector<int>> inverse(MAXN); // lista de adj do grafo inverso
vector<bool> vis(MAXN,false); // vertices visitados
stack<int> stk; // guardar a ordem dos vtx

// DFS no grafo normal para descobrir a ordem inversa que iremos passar no grafo inverso
void dfsGraphNormal(int idx) {
    for(auto e : adj[idx]) {
        if(!vis[e]) {
            vis[e] = true;
            dfsGraphNormal(e);
        }
    }
    stk.push(idx); // pilha que guardara a ordem dos vertices
}

// DFS no grafo inverso para achar as componentes fortemente conexas do grafo
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
            
            adj[x].push_back(y); // add aresta no grafo original
            inverse[y].push_back(x); // add aresta no grafo inverso
            
            if(z != 1) { // se z != 1, então a rua é mão dupla e devo adicionar outra aresta indicando isso
                adj[y].push_back(x);
                inverse[x].push_back(y);
            }
        }

        // dfs no grafo original
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                vis[i] = true;
                dfsGraphNormal(i);
            }
        }

        int ans = 0; // numero de componentes fortemente conexas no grafo (resposta)

        for(int i = 1; i <= n; i++) { // resetando array vis
            vis[i] = false;
        }

        // dfs no grafo inverso
        while(!stk.empty()) {
            int e = stk.top();
            stk.pop();
            if(!vis[e]) {
                vis[e] = true;
                ans++;
                dfsGraphInv(e);
            }
        }

        if(ans > 1) { // mais de 1 comp. fort. conexa
            cout << "0\n";
        } else { // apenas 1 comp. fort. conexa
            cout << "1\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve(); // funcao que resolve tudo
}