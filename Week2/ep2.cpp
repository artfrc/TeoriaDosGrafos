// https://open.kattis.com/problems/runningmom

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5123*2;

typedef vector<vector<int>> vvi;

vvi adj(MAXN); // lista de adjacencia dos vertices do grafo
vvi reverseAdj(MAXN); // grafo com lista de adj reversa
map<string,int> mp; // armazenar o indice de cada cidade
stack<int> stk; // ordem dos vertices por tempo
bool vis[MAXN]; // dizer se um vertice ja foi visitado
vector<int> idxComponents(MAXN,-1); // guarda qual componente cada vertice pertence
vector<int> nElementsComponents(MAXN,0); // numero de elementos q contem cada componente
int nComponents; // numero total de componentes do grafo

void dfs(int idx) {
    for(auto e : adj[idx]) {
        if(!vis[e]) {
            vis[e] = true;
            dfs(e);
        }
    }
    stk.push(idx);
}

void dfs2(int idx) {
    for(auto e : reverseAdj[idx]) {
        if(idxComponents[e] == -1) {
            idxComponents[e] = nComponents;
            nElementsComponents[nComponents]++;
            dfs2(e);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    
    int nCitys = 0;

    for(int i = 0; i < n; i++) {
        string c1, c2;
        cin >> c1 >> c2;

        if(mp.find(c1) == mp.end()) { // nova cidade para o grafo
            mp[c1] = nCitys; // cidade c1 será o indice nCitys no vector adj
            nCitys++;
        }

        if(mp.find(c2) == mp.end()) { // nova cidade para o grafo
            mp[c2] = nCitys; // cidade c2 será o indice nCitys no vector adj
            nCitys++;
        }

        int idxCity1 = mp[c1];
        int idxCity2 = mp[c2];

        adj[idxCity1].push_back(idxCity2);
        reverseAdj[idxCity2].push_back(idxCity1);
    }
        
    // Algoritmo de Kosaraju's => Irá encontrar as componentes fortemente conexas do grafo
    
    // Passo 1: dfs
    memset(vis,false,sizeof(vis));
    for(int i = 0; i < nCitys; i++) {
        if(!vis[i]) {
            vis[i] = true;
            dfs(i);
        } 
    }

    // Passo 2: grafo reverso, outra dfs e encontrar as componentes
    nComponents = 0;
    while(!stk.empty()) {
        int v = stk.top();
        stk.pop();
        if(idxComponents[v] == -1) {
            idxComponents[v] = nComponents;
            nElementsComponents[nComponents]++;
            dfs2(v);
            nComponents++;
        }
    }

    string city;
    while(cin >> city) {
        int idxCity = mp[city];
        int idxComponentCity = idxComponents[idxCity];
        if(nElementsComponents[idxComponentCity] > 1) cout << city << " safe\n";
        else cout << city << " trapped\n";
    }    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}