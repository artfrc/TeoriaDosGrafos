// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=2870

#include <bits/stdc++.h>
using namespace std;

/* ============================================== >> EXPLICACAO << ==============================================
|
|    O problema consiste em um campo que contem postes de luzes e o personagem comprou luzes inteligentes para esses postes.
|    Dependendo da distancia entre dois postes, quando o A acende a luz, se o poste B tiver perto suficiente, então poste B acende, 
|    se tiver um C por perto, então o C tbm acende e assim por diante. Para ligar um poste, o personagem tem q apertar um botão. 
|    Enfim, o problema quer saber quantas vezes o personagem tem que apertar o botão para acender todas as luzes do campo.
|    Em outras palavras, quer saber o número de componentes fortemente conexas. Basta usar o algoritmo de Kosaraju's visto em sala.
|
|  ============================================== >> EXPLICACAO << ============================================== */

typedef vector<vector<int>> vvi;

const int MAX = 11234; // numero maximo de vertices que o grafo do problema pode ter

bool vis[MAX] = {false};
vvi adj(MAX);
set<pair<int,int>> st; // {nro. adj/vtx}

// DFS no grafo inverso para achar as componentes fortemente conexas do grafo
void dfsGraph(int idx) {
    for(auto e : adj[idx]) {
        if(!vis[e]) {
            vis[e] = true;
            dfsGraph(e);
        }
    }
}

void solve() {
    int t, c = 0;
    int nVertex, nEdges;
    cin >> t;
    while(t--) {
        cout << "Case " << ++c << ": ";

        cin >> nVertex >> nEdges;
        
        for(int i = 0; i < nEdges; i++) {
            int v1, v2;
            cin >> v1 >> v2;
            
            adj[v1].push_back(v2);
        }

        for(int i = 1; i <= nVertex; i++) {
            st.insert({adj[i].size(),i});
        }

        int ans = 0;

        for(auto it = st.rbegin(); it != st.rend(); it++) {
            if(!vis[it->second]) {
                ++ans;
                vis[it->second] = true;
                dfsGraph(it->second);
            }
        }

        cout << ans << "\n";

        // Resetar variaveis
        for(int i = 1; i <= nVertex; i++) {
            adj[i].clear();
            vis[i] = false;
        }
        st.clear();
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}