#include <bits/stdc++.h>
using namespace std;

const int MAXN = 11234;

typedef vector<vector<int>> vvi;

vvi adjNormal(MAXN); // lista adj grafo normal
vvi adjInv(MAXN); // lista adj do grafo invertido
bool vis[MAXN];
bool blind[MAXN]; // diz se o vértice tem grau de entrada zero no grafo original

// Primeira DFS do algortimo de kosaraju's
void dfsGraphNormal(int idx, stack<int>& stk) {
    vis[idx] = true;
    for(auto e : adjNormal[idx]) {
        if(!vis[e]) {
            dfsGraphNormal(e,stk);
        }
    }
    stk.push(idx);
}

// Segunda DFS do algoritmo de kosaraju's
void dfsGraphInv(int idx, int& ans) {
    vis[idx] = true;
    
    if(blind[idx]) { // é um vertice que não vai para lugar nenhum, logo é uma luz que precisa ser ligada manualmente
        ans++;
        return;
    }

    bool passBlind = false; // diz se idx eh um vertice que chega em algum outro vertice que é blind (luz que precisa ser ligada manualmente)

    for(auto e : adjInv[idx]) {
        
        if(blind[e]) {
            // atraves do vertice "e", a luz idx é acesa, ou seja, não é preciso ligar manualmente a luz "idx"
            passBlind = true;
            break;
        }

        if(!vis[e]) {
            dfsGraphInv(e,ans);
        } else {
            // se estou em uma luz que já foi visitada, entao quer dizer que essa será acesa automaticamente tb
            passBlind = true;
        }
    }

    if(!passBlind) ++ans; // se não passei por nenhuma luz que já foi ligada entao deve ser acendida manualmente
}

void solve() {
    int t, count = 0;
    cin >> t;
    
    while(t--) {
        int vtx, edges;
        cin >> vtx >> edges;

        // Resetando variaveis
        for(int i = 0; i< edges; i++) {
            adjNormal[i].clear();
            adjInv[i].clear();
            vis[i] = false;
            blind[i] = true;
        }

        // Leitura da entrada
        for(int i = 0; i < edges; i++) {
            int v1, v2;
            cin >> v1 >> v2;
            adjNormal[v1].push_back(v2);
            adjInv[v2].push_back(v1);
            blind[v2] = false; // vertice não possui grau de entrada zero
        }

        stack<int> stk;

        // Pt. 1 algoritmo kosaraju's
        for(int i = 0; i < vtx; i++) {
            if(!vis[i]) {
                dfsGraphNormal(i,stk);
            }
        }

        memset(vis,false,sizeof(vis));

        int ans = 0;

        // Pt. 2
        while(!stk.empty()) {
            auto e = stk.top();
            stk.pop();
            if(!vis[e]) {
                dfsGraphInv(e,ans);
            }
        }
        cout << "Case " << ++count << ": " << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}