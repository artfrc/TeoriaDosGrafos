// https://www.beecrowd.com.br/judge/pt/problems/view/3215

#include <bits/stdc++.h>
using namespace std;


/* ===========================================================================================================================================
    O problema consiste em um grafo com n vértices e m arestas. Cada vértice é uma pessoa e cada aresta ligando dois vértices significa uma amizade entre essas duas pessoas.
    Para resolver o problema, basta verificar se a soma de cada componente conexa resultará em zero. Pois se resultar em zero, quer dizer que todos naquela componente conexa consegue ficar sem dívidas. (Leia o problema caso não entendeu essa explicação)

    Para achar cada componente conexa, usei uma dfs.
    Através de um vértice x, através da dfs, eu consigo achar todos os elementos que estão na mesma componente que ele.
    Toda as vezes que eu chamo a dfs para um determinado vértice, significa que achei uma nova componente conexa.
    Veja o codigo para melhor entendimento.
=========================================================================================================================================== */

const int MAXN = 10123; // numero maximo de N (numero de amigos)

int n,m; // numero de amigos e numero de amizades, respectivamente
vector<int> values; // vetor que contem a quantia que cada pessoa deve/é devida
vector<vector<int>> adj(MAXN); // lista de adjacencias
bool vis[MAXN] = {false}; // array para saber quais vertices foram visitados
int debit; // soma de uma componente conexa. Se for diferente de zero, quer dizer que alguem da componente conexa não ficou com saldo 0

void dfs(int idx) {
    vis[idx] = true;
    debit += values[idx]; // somando o saldo da componente
    for(auto e : adj[idx]) {
        if(vis[e]) continue; // se já visitei esse vértice, então não preciso visitar mais
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

        // adicionando arestas no grafo (lista de adjacencia)
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    bool ans = true;

    for(int i = 0; i < n and ans; i++) {
        if(!vis[i]) {
            debit = 0;
            dfs(i);
            if(debit != 0) { // alguma pessoa dessa componente ficou com divida ou devendo alguém
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