#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10123; // numero maximo de N (numero de amigos)

int n,m; // numero de amigos e numero de amizades, respectivamente
vector<int> values; // vetor que contem a quantia que cada pessoa deve/é devida
vector<vector<int>> adj(MAXN); // lista de adjacencias
vector<vector<int>> components(MAXN); // lista de componentes conexas
bool vis[MAXN] = {false}; // array para saber quais vertices foram visitados
int debit; // soma de uma componente conexa. Se for diferente de zero, quer dizer que alguem da componente conexa não ficou com saldo 0

void dfs(int idx) {
    vis[idx] = true;
    debit += values[idx]; // somando o saldo da componente
    for(auto e : adj[idx]) {
        if(vis[e]) continue;
        dfs(e);
    }
}

void solve() {
    // Entrada de dados
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int v; cin >> v;
        values.push_back(v);
    }

    for(int i = 0; i < m; i++) {
        int x,y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    bool ans = true;

    for(int i = 0; i < n and ans; i++) {
        if(!vis[i]) {
            debit = 0;
            dfs(i);
            if(debit != 0) {
                ans = false;
            }
        }            
    }

    if(ans) cout << "POSSIBLE\n";
    else    cout << "IMPOSSIBLE\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}