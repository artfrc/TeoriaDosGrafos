// https://open.kattis.com/problems/runningmom

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5123 * 2; // numero maximo de cidades que pode ter no problema
map<string,int> mp; // mapeia o nome da cidade para um indice
vector<vector<int>> adj(MAXN); // lista de adjacencia do grafo
vector<int> degree(MAXN,0); // grau de cada vértice
bool vis[MAXN]; // marca se um vertice ja foi visitado
int nCitys = 0; // numero de cidades

void solve() {
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        string city1, city2;
        cin >> city1 >> city2;

        if(mp.find(city1) == mp.end()) {
            mp[city1] = nCitys;
            nCitys++;
        }

        if(mp.find(city2) == mp.end()) {
            mp[city2] = nCitys;
            nCitys++;
        }

        int idxCity1 = mp[city1];
        int idxCity2 = mp[city2];

        adj[idxCity2].push_back(idxCity1);
        degree[idxCity1]++; // grau de cada vértice
        // grafo original: grau de saída
        // grafo transposto: grau de entrada
    }

    queue<int> q;

    // adicionamos na fila todas as cidades com grau 0, ou seja, cidades trappeds
    for(int i = 0; i < nCitys; i++) {
        if(degree[i] == 0) q.push(i);
    }

    // verificamos todas as cidades que nos levam a uma cidade trapped e "retiramos" essa aresta do grafo (dregree[e]--)
    while(!q.empty()) {
        int idx = q.front();
        q.pop();
        for(auto e : adj[idx]) {
            degree[e]--;
            if(degree[e] == 0) q.push(e);
        }
    }

    string city;
    
    while(cin >> city) {
        int idxCity = mp[city];
        if(degree[idxCity] < 1) cout << city << " trapped\n"; 
        else cout << city << " safe\n";
    } 
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}