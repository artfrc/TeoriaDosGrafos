// https://open.kattis.com/problems/kingpinescape

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+59; // numero max de vertices que pode conter o grafo

typedef vector<vector<int>> vvi;

vector<int> leaves; // guardar as folhas do grafo
vector<bool> vis(MAXN,false);
vvi adj(MAXN);

void dfs(int idx) {
    vis[idx] = true;

    bool isLeaf = true;
    for(auto viz : adj[idx]) {
        if(!vis[viz]) {
            isLeaf = false;
            dfs(viz);
        }
    }

    if(isLeaf) {
        leaves.push_back(idx);
    }
}

void solve() {
    int n, begin;
    cin >> n >> begin;

    for(int i = 0; i < n-1; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }

    dfs(begin);

    if(adj[begin].size() == 1) {
        leaves.push_back(begin);
    }

    int nLeaves = leaves.size();

    // Como iremos conectar todas as folhas, então o número de arestas será o número de folhas +1 dividido por 2.
    // O +1 é devido acontecer ser número impar de folhas
    int nNewEdges = (nLeaves+1) / 2;

    cout << nNewEdges << endl;

    // Para saber as folhas q foram conectadas uma com as outras, o vetor "leaves" é dividido na metade. Então pegamos a primeira folha da metade 1 e ligamos com a primeira folha da metade 2 e assim por diante.
    for(int i = 0; i < nNewEdges; i++) {
        cout << leaves[i] << " " << leaves[(i+(nLeaves / 2)) % nLeaves] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}