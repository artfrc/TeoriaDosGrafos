#include <bits/stdc++.h>
using namespace std;

const int MAX = 8;

typedef pair<int,int> pii;

int r1,r2,r3;
int c1,c2,c3;
int dist[MAX][MAX]; // matriz que guarda as distancias

// direcoes que o rei pode andar em um lance (esquerda, direita, cima, baixo e diagonais)
int arrx[] = {-1,1,0,0,-1,-1,1,1};
int arry[] = {0,0,-1,1,-1,1,-1,1};
    
void dijkstra(int row, int column) {

    memset(dist,-1,sizeof(dist)); // reseta todas distancias para -1

    set<pair<int,pii>> Queue; // substitui a priority_queue
    Queue.insert({0,{row,column}}); // { dist, {row,column} }
    pair<int,pii> aux;
    
    while(!Queue.empty()) {
        aux = *Queue.begin();
        Queue.erase(Queue.begin());
        row = aux.second.first;
        column = aux.second.second;
        int distv = aux.first;
        
        // se for uma posição no tabuleiro que ainda não passei...
        if(dist[row][column] == -1) {
            dist[row][column] = distv; // atualizo sua distancia

            if(row == r2 and column == c2) return; // ja achei a dist do ponto desejado, paro aqui
            
            // vejo todos os vizinhos possíveis (esquerda, direita, ...)
            for(int i = 0; i < 8; i++) {
                int newRow = row+arrx[i];
                int newColumn = column+arry[i];

                // posicoes invalidas
                if(newRow < 0 or newRow >= MAX or newColumn < 0 or newColumn >= MAX) continue; // fora da matriz
                if((newRow == r3 and newColumn == c3) or dist[newRow][newColumn] != -1) continue; // posição retirada no input ou posição ja visitada
                
                Queue.insert({ distv+1, {newRow,newColumn} });
            }
        }
    }
    
}

void solve() {

    int Case = 0;

    while(cin >> r1 >> c1 >> r2 >> c2 >> r3 >> c3) {
        r1--; c1--; r2--; c2--; r3--; c3--;
        dijkstra(r1,c1); // chamo dijkstra começando pela coordenada inicial do rei (r1,c1)
        cout << "Case " << ++Case << ": " << dist[r2][c2] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}