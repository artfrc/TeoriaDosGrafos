#include <bits/stdc++.h>
using namespace std;

/* ===========================================================================================================================================
    O problema consiste em verificar se um grafo pode ser colorido apenas usando duas cores. (bicoloração)
    Isso só pode acontecer se o grafo for bipartido, pois em um grafo bipartido, conseguimos separar o grafo em dois conjuntos de vértices, onde um vértice do conjunto X nunca terá conexão (aresta) com um vértice do mesmo conjunto que ele. Logo, podemos colorir um conjunto de vértices de uma cor e o outro conjunto de outra cor.

    Usando BFS, chamamos um vértice qualquer para iniciar essa BFS, damos uma cor para esse vértice. Então colorimos todos seus vizinhos da cor oposta.
    Caso algum vizinho já esteja colorido, devemos verificar a cor dele. Se forem da mesma cor, quer dizer que não é um grafo bipartido. Retorno falso e posso encerrar a busca.
=========================================================================================================================================== */

const int MAXNODES = 222; // numero maximo de nos que o grafo pode conter

int nodes, edges; // numero de nos e arestas do grafo, respectivamente
vector<vector<int>> adj(MAXNODES); // lista de adjacencia do grafo
int colors[MAXNODES]; // guarda a cor de cada vértice

bool bfs(int idx) {
    queue<int> q;
    q.push(idx);
    colors[idx] = 1;
    while(!q.empty()) {
        int currentIdx = q.front();
        q.pop();
        for(auto nxt : adj[currentIdx]) {
            if(colors[nxt] == 0) { // não está colorido
                colors[nxt] = colors[currentIdx]*(-1); // cor inversa
                q.push(nxt);
            } else { // já foi colorido
                if(colors[nxt] == colors[currentIdx]) return false; // nao eh um grafo bipartido
            }
        }
    }
    return true;
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

        if(bfs(0)) cout << "BICOLORABLE.\n";
        else cout << "NOT BICOLORABLE.\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}