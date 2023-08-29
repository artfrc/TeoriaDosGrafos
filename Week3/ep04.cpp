// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=4648

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e3+123; // numero maximo de vertices que o problema pode ter

vector<vector<int>> adj(MAXN); // lista de adj
vector<bool> vis(MAXN,false); // vetor de visitados
vector<int> low(MAXN,-1); // tempo de descoberta mínimo entre todos os vértices acessíveis a partir de u na DFS
vector<int> des(MAXN,-1); // tempo de descoberta do vertice
vector<int> parent(MAXN,-1); // pai de cada vértice
vector<pair<int,int>> bridges; // pontes do grafo
int temp = 0; // marca o tempo
int ans = 0; // resposta

// Função para procurar as pontes do grafo
void findBridges(int idx) {
    vis[idx] = true;

    // marcando o tempo de descoberta
    low[idx] = ++temp; 
    des[idx] = temp; 

    for(auto viz : adj[idx]) { // passar pelos adj de idx através de uma dfs
        if(!vis[viz]) {
            parent[viz] = idx; // marco quem é o pai do vizinho de idx
            findBridges(viz);
            low[idx] = min(low[idx],low[viz]);

            if(low[viz] > des[idx]) {
                // se low[viz] > des[idx] significa que  a aresta {viz,idx} é uma ponte, pois o vertice viz foi descoberto após o idx e não há um caminho que leve viz de volta para idx (não há um ciclo)
                if(viz < idx) {
                    bridges.push_back({viz,idx});
                } else {
                    bridges.push_back({idx,viz});
                }
            }
        } else if(viz != parent[idx]) {
            low[idx] = min(low[idx],low[viz]);
        }
    }
}

void solve() {
    int N,M;
    while(1) {
        cin >> N >> M;
        if(N == 0 and M == 0) return;
    
        for(int i = 0; i < N; i++) {
            adj[i].clear();
            vis[i] = false;
        }

        bridges.clear();

        for(int i = 0; i < M; i++) {
            int v1,v2;
            cin >> v1 >> v2;
            adj[v1].push_back(v2);
            adj[v2].push_back(v1);
        }

        for(int i = 0; i < N; i++) {
            if(!vis[i]) {
                findBridges(i);
            }
        }

        sort(bridges.begin(),bridges.end());

        bool flag = false;
        cout << bridges.size();
        
        if(bridges.size() != 0) {
            cout << " ";
        }

        for(auto e : bridges) {
            if(flag) cout << " ";
            flag = true;
            cout << e.first << e.second;
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();
}