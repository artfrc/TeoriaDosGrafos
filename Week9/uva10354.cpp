#include <bits/stdc++.h>
using namespace std;

/*
    Ideia do codigo foi:
        - achar o menor caminho da casa do chefe até o escritório
            (inclui achar as arestas que estão nesse menor caminho)
        
        - tentar chegar ao mercado usando uma dfs sem passar pelas arestas do menor caminho encontrado antes e também sem passar pela casa ou escritório do chefe
*/

const int MAXP = 123;

typedef vector<vector<pair<int,int>>> vvp;

int P,R,BH,OF,YH,M;
vvp adj(MAXP);
int dist[MAXP];
pair<int,int> whoCalled[MAXP]; // auxilia para encontrar as arestas do menor caminho de BH ate OF
bool path[MAXP][MAXP]; // marca as arestas que compoe o menor caminho de BH ate OF
bool vis[MAXP];
bool ans;

void dijkstra(int idx) {

    memset(dist,-1,sizeof(dist));
    memset(whoCalled,-1,sizeof(whoCalled));

    set<pair<int,int>> st;
    st.insert({0,idx});

    pair<int,int> aux;

    while(!st.empty()) {
        aux = *st.begin();
        st.erase(st.begin());

        int currentIdx = aux.second;
        int distance = aux.first;

        if(dist[currentIdx] == -1) {
            dist[currentIdx] = distance;

            if(currentIdx == OF) return;

            for(auto neighboor : adj[currentIdx]) {

                int idxNeigh = neighboor.second;
                int distNeigh = neighboor.first;


                if(dist[idxNeigh] == -1) {
                    st.insert({ distNeigh+distance, idxNeigh });

                    // Auxilia para dizer quem chamou tal vertice
                    if((whoCalled[idxNeigh].first == -1) or (whoCalled[idxNeigh].first > distNeigh+distance)) {
                        whoCalled[idxNeigh].first = distNeigh+distance;
                        whoCalled[idxNeigh].second = currentIdx;
                    }
                }
            }
        }
    }

}

int dfs(int idx) {
    if(ans) return 0;

    if(idx == M and idx != BH and idx != OF) {
        ans = true;
        return 0;
    }

    vis[idx] = true;

    for(auto neighboor : adj[idx]) {
        int idxNeigh = neighboor.second;
        if(!vis[idxNeigh] and !path[idx][idxNeigh] and idxNeigh != BH and idxNeigh != OF) {
            return neighboor.first+dfs(idxNeigh);
        }
    }

    return 0;

}

void solve() {

    while(cin >> P >> R >> BH >> OF >> YH >> M) {

        // Reset data
        ans = false;
        memset(vis,false,sizeof(vis));
        for(int i = 1; i <= P; i++) {
            adj[i].clear();
        }

        // Le dados grafo
        for(int i = 0; i < R; i++) {
            int p1, p2, d;
            cin >> p1 >> p2 >> d;

            adj[p1].push_back({d,p2});
            adj[p2].push_back({d,p1});
        }

        // Achar menor caminho de BH até OF
        dijkstra(BH);

        memset(path,false,sizeof(path));

        // Achar arestas que compoe esse menor caminho
        int flag = OF;
        while(1) {
            int called = whoCalled[flag].second;
            path[flag][called] = true;
            path[called][flag] = true;

            if(called == BH) break;

            flag = called;
        }

        // Verifica se há um caminho de YH até M sem passar pelas arestas de path ou pelo vertice BH ou OF
       int x = dfs(YH);

        if(ans) {
            cout << x << "\n";
        } else {
            cout << "MISSION IMPOSSIBLE\n";
        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}