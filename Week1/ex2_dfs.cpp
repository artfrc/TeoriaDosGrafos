// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=945

#include <bits/stdc++.h>
using namespace std;

/* ===========================================================================================================================================
    É a mesma ideia do codigo usando BFS, porém aqui o modo de visitar os vértices é diferente. (dfs)
=========================================================================================================================================== */

const int MAXNODES = 222; // numero maximo de nos que o grafo pode conter

int nodes, edges; // numero de nos e arestas do grafo, respectivamente
vector<vector<int>> adj(MAXNODES); // lista de adjacencia do grafo
int colors[MAXNODES]; // guarda a cor de cada vértice
bool ans; // auxilia para saber se o grafo é bipartido ou não

void dfs(int idx) {
    for(auto nxt : adj[idx]) {
            if(colors[nxt] == 0) { // não está colorido
                colors[nxt] = colors[idx]*(-1); // cor inversa
                dfs(nxt);
            } else { // já foi colorido
                if(colors[nxt] == colors[idx]) { // nao eh um grafo bipartido
                    ans = false;
                    return;
                }
            }
        }
}

void solve() {
    while(cin >> nodes) {
        if(nodes == 0) return;
        cin >> edges;

        // Como são varios casos testes, preciso resetar minha lista de adjacencia para cada teste novo
        for(int i = 0; i < nodes; i++) {
            adj[i].clear();
        }

        for(int i = 0; i < edges; i++) {
            int x,y;
            cin >> x >> y;

            // Arestas do grafo
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        memset(colors,0,sizeof(colors)); // setando todos os vertices para cor 0 (ainda n foi colorido)

        ans = true; // suponho que o grafo é bipartido
        colors[0] = 1;

        dfs(0); // inicio a dfs no vértice 0

        if(ans) cout << "BICOLORABLE.\n";
        else cout << "NOT BICOLORABLE.\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}