#include <bits/stdc++.h>
using namespace std;

/*
    O problema se resume em achar o número de componentes conexas que contem o grafo.
    Podemos interpretar a matriz dada no problema como um grafo.
*/

const int MAX = 123; // número maximo de linhas e colunas que pode conter a matriz

string arr[MAX]; // matriz
bool vis[MAX][MAX]; // matriz para indicar as posições ja visitadas
int ans, rows, columns;

// arrays que auxiliam no percorrimento da matriz (DFS)
int dx[] = {-1,-1,-1,1, 1,1, 0,0}; // se refere a linha da matriz
int dy[] = { 0,-1, 1,0,-1,1,-1,1}; // se refere a coluna da matriz

/* ==========================================================================================
|    EXEMPLO: Estamos na posição (2,3) da matriz
|    se índice de dx e dy for 0 e queremos se movimentar, então a nova posição será:
|    (2+dx[0], 3+dy[0]) = (2+(-1), 3+0) = (1,3)
|    Ou seja, de (2,3) fomos para (1,3). Fomos uma posição para cima
|    Segue o mesmo raciocínio para os demais índices.
|    índice = 0 => movimento para cima
|    índice = 1 => movimento para diagonal superior esquerda
|    índice = 2 => movimento para diagonal superior direita
|    índice = 3 => movimento para baixo
|    índice = 4 => movimento para diagonal inferior esquerda
|    índice = 5 => movimento para diagonal inferior direita
|    índice = 6 => movimento para esquerda
|    índice = 7 => movimento para direita  
|  ========================================================================================== */ 

void dfs(int x, int y) { // x e y é a posição em que irei começar percorrer a matriz através da DFS
    
    // Procurando todas as posições que contem '@' e são adjacentes a arr[x][y]
    // (elementos da nova componente conexa)
    for(int i = 0; i < 8; i++) {

        // calculando nova posição
        int nx = x+dx[i];
        int ny = y+dy[i];
        
        // verificação se é uma posição válida ou é diferente de '@' ou então se já foi visitado
        if(nx < 0 or nx >= rows or ny < 0 or ny >= columns or arr[nx][ny] != '@' or vis[nx][ny]) continue;
        
        vis[nx][ny] = true;
        dfs(nx,ny);
    }
}

void solve() {
    while(cin >> rows >> columns) { // Leitura dos dados de entrada (numero de linhas e coluna da matriz)
        if(rows == 0) return; // termina as entradas e encerra o problema

        memset(vis,false,sizeof(vis)); // seto todas as posições da matriz 
        ans = 0;

        // Leitura da matriz de entrada
        for(int i = 0; i < rows; i++) {
            cin >> arr[i];
        }

        // percorrendo a matriz
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                if(arr[i][j] == '@' and !vis[i][j]) { // encontrei uma nova componente conexa
                    ans++; // +1 componente
                    vis[i][j] = true;
                    dfs(i,j); // marco todas as posições que fazem parte dessa componente
                }
            }
        }
        // Saída
        cout << ans << "\n";
    }
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}