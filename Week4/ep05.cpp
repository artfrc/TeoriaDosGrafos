// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=3670

#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> vvi;

const int MAX = 123;

map<string,int> mp; // armazenar o index de cada palavra
bool arr[MAX][MAX]; // matriz de adj
bool vis[MAX];
vvi adj(MAX); // lista de adj grafo normal
vvi adjInv(MAX); // lista de adj grafo inv

void dfsGraphNormal(int idx, stack<int>& stk) {
    vis[idx] = true;
    for(auto e : adj[idx]) {
        if(!vis[e]) {
            dfsGraphNormal(e,stk);
        }
    }
    stk.push(idx); // finalizando a dfs de idx entao insiro na pilha
}

void dfsGraphInv(int idx, set<string>& st) {
    /* ==========================================================================================
        Essa dfs é passado tbm como parametro um Set para ir armazenando a componente fortemente conexa encontrada na dfs.
    |  ========================================================================================== */
    vis[idx] = true;
    
    // Buscando o nome da cidade com index "idx" para inserir no Set
    for(auto it = mp.begin(); it != mp.end(); it++) {
        if(it->second == idx) {
            st.insert(it->first);
            break;
        }
    }

    // Parte normal de uma dfs (recursao)
    for(auto e : adjInv[idx]) {
        if(!vis[e]) {
            dfsGraphInv(e,st);
        }
    }
}

void solve() {

    int n;
    string line;

    while(cin >> n) {
        if(n == 0) return;
        
        getline(cin,line);

        // Resetando variaveis
        int words = 0;
        memset(arr,false,sizeof(arr));
        memset(vis,false,sizeof(vis));

        // Leitura do input e criacao das listas de adj
        for(int i = 0; i < n; i++) {
            getline(cin,line);
            int count = 0, idxWord, idxDefinition;
            stringstream SS(line);
            while(SS >> line) {
                if(mp[line] == 0) {
                    mp[line] = ++words;
                }

                if(!count) {
                    ++count;
                    idxWord = mp[line];
                } else {
                    idxDefinition = mp[line];
                    if(!arr[idxWord][idxDefinition]) {
                        arr[idxWord][idxDefinition] = true;
                        adj[idxWord].push_back(idxDefinition);
                        adjInv[idxDefinition].push_back(idxWord);
                    }
                }
            }
        }

        // kosaraju's algorithm
        stack<int> stk;

        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                dfsGraphNormal(i,stk);
            }
        }

        vector<set<string>> ans;
        set<string> st;

        // minSizeSt é para guardar o tamanho da menor componente fortemente conexa, tal que é > 1.
        // flag é para guardar o index do vector "ans" que está minha componente
        int minSizeSt = 9999, flag;

        memset(vis,false,sizeof(vis));

        // Segunda parte do kosaraju's algorithm
        while(!stk.empty()) {
            auto e = stk.top();
            stk.pop();
            st.clear();
            if(!vis[e]) {
                dfsGraphInv(e,st);
                ans.push_back(st);
                if(st.size() > 1 and minSizeSt > st.size()) {
                    flag = st.size()-1;
                    minSizeSt = st.size();
                }
            }
        }

        // Pritando saída do problema
        bool space = false;

        for(auto it = ans[flag].begin(); it != ans[flag].end(); it++) {
            if(space) cout << " ";
            space = true;
            cout << *it;
        }
        cout << "\n";

    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}