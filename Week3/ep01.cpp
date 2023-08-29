// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=251

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e2 + 23; // numero maximo de vertices que pode ter o grafo do exercicio
vector<vector<int>> adj(MAXN);  // lista de adj do grafo
bool visited[MAXN]; // vetor de visitados
int disc[MAXN], low[MAXN], parent[MAXN]; // disc = discovery time, low = menor discovery time que pode ser alcançado por um vertice, parent = pai de um vertice
int t,ans; // t = tempo, ans = resposta

// Função para encontrar os pontos de articulação
void articulationPoints(int idx) {
    int children = 0; // numero de filhos q idx tem
    visited[idx] = true;
    ++t; disc[idx] = t; low[idx] = t;

    for(auto viz : adj[idx]) {
        if(!visited[viz]) {
            children++;
            articulationPoints(viz);

            low[idx] = min(low[idx], low[viz]);

            // Se idx não é raiz e low[viz] >= disc[idx], então idx é um ponto de articulação, pois não existe nenhum caminho de volta para um ancestral de idx
            if(parent[idx] != -1 and low[viz] >= disc[idx]) {
                ans++;
            }
        } else if(viz != parent[idx]) { // Se viz já foi visitado e não é o pai de idx, então atualizamos o low de idx
            low[idx] = min(low[idx], disc[viz]);
        }
    }

    // Se idx é raiz e tem mais de um filho, então idx é um ponto de articulação
    if(parent[idx] == -1 and children > 1) ans++;
}

void solve() {
    int N;
    string line;
    while(cin >> N) {
        getline(cin,line);
        if(N == 0) break;

        // Resetando as variáveis
        t = 0;
        ans = 0;
        for(int i = 0; i <= N; i++) {
            adj[i].clear();
            visited[i] = false;
            disc[i] = low[i] = 0;
            parent[i] = -1;
        }

        // Modo para ler a entrada do problema
        while(getline(cin,line)) {
            if(line[0] == '0') break;
            stringstream ss(line);
            int u,v;
            ss >> u;

            // Criando as adj do grafo
            while(ss >> v) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }

        for(int i = 1; i <= N; i++) {
            if(!visited[i]) {
                articulationPoints(i);
            }
        }

        cout << ans << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();
}