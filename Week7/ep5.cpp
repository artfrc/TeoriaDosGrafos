#include <bits/stdc++.h>
using namespace std;

const int MAXR = 10; // maximo de botoes que pode ter

typedef pair<int,int> pii;

int l,u,r;
int bottons[MAXR]; // valor de cada botao
set<int> discoveredVtx; // vertices que ja descobri
vector<int> temp; // tempo de descoberta de cada possível senha
vector<int> valueIdx; // valor armazenado no vertice

// Praticamente Dijkstra normal
void dijkstra(int v) {

    discoveredVtx.insert(l); // descobri o valor inicial ( l )
    temp.push_back(0); // temp[0] = 0
    valueIdx.push_back(l); // value[0] = l;
    
    pii aux;
    set<pii> Queue; // poderia ser priority_queue no lugar do set, mas o set já ordena
    Queue.insert({0,v}); // { tempo de descoberta, idx do vertice }
    
    while(!Queue.empty()) {
        aux = *Queue.begin();
        Queue.erase(Queue.begin());
        
        int tempv = aux.first; // tempo de descoberta do vertice
        int idx = aux.second; // idx do vertice

        // Fazer a soma com todos os botoes possíveis
        for(int i = 0; i < r; i++) {
            int newValue = valueIdx[idx]+bottons[i];
            if(newValue > 9999) {
                // pegar apenas os 4 digitos menos significativos
                newValue -= 10000;
                /*
                    A subtração por 10000 é suficiente pois o valor maximo que pode ser atingido nesse newValue será 19998 (9999 + 9999). Logo, basta subtrair 10000 para obter apenas os 4 digitos menos significativos
                */
            }

            if(discoveredVtx.find(newValue) == discoveredVtx.end()) { // valor ainda não foi descoberto
                Queue.insert({ tempv+1, valueIdx.size() });
                discoveredVtx.insert(newValue); // adiciono o valor na estrutura pra saber que ja descobri ele
                valueIdx.push_back(newValue); // guardo o valor dele (valueIdx[0] guarda o valor do vertice 0, valueIdx[1] guarda o valor do vertice 1, ...)
                temp.push_back(tempv+1); // guardo o tempo de descoberta (mesma logica do valueIdx)
            }

            if(newValue == u) return; // encontrei o valor procurado, para o dijkstra
        }
    }
    
}

void solve() {

    int Case = 0;

    while(cin >> l >> u >> r) {
        if(l == 0 and u == 0 and r == 0) return;
        
        // Resetando estruturas
        valueIdx.clear();
        temp.clear();
        discoveredVtx.clear();

        // Lendo o valor de cada botão
        for(int i = 0; i < r; i++) cin >> bottons[i];

        // Chamo a função começando do vertice 0, ou seja, vértice com valor "l"
        dijkstra(0);

        cout << "Case " << ++Case << ": ";
        if(valueIdx.back() != u) cout << "Permanently Locked\n"; // não é possível chegar no valor "u"
        else cout << temp[valueIdx.size()-1] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}