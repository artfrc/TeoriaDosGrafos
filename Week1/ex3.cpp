// https://www.beecrowd.com.br/judge/pt/problems/view/1855

#include <bits/stdc++.h>
using namespace std;

/*
    O problema consiste em achar o baú.
    É dado uma matriz que pode ser interpretada como um grafo.
    Devemos percorrer essa matriz e verificar se é possível chegar até o baú (caracter '*')
*/

const int MAX = 123; // Número máximo de linhas e colunas que a matriz pode ter

int columns, rows; // número de colunas e linhas
string arr[MAX]; // matriz
bool vis[MAX][MAX] = {false}; // matriz para verificar posições que já foram visitadas
bool ans = false; // variável para dizer se encontramos o caracter '*'

// arrays que auxiliam no percorrimento da matriz (DFS)
int dx[] = {-1,1,0,0}; // se refere a linha da matriz
int dy[] = {0,0,-1,1}; // se refere a coluna da matriz

int direction; // guarda o índice dos arrays dx e dy (saber qual direção está indo)

/* ==========================================================================================
|    EXEMPLO: Estamos na posição (2,3) da matriz
|    se direction for 0 e queremos se movimentar nessa direção, então a nova posição será:
|    (2+dx[0], 3+dy[0]) = (2+(-1), 3+0) = (1,3)
|    Ou seja, de (2,3) fomos para (1,3). Fomos uma posição para cima
|    Segue o mesmo raciocínio para os demais índices.
|    direction = 0 => movimento para cima
|    direction = 1 => movimento para baixo
|    direction = 2 => movimento para esquerda
|    direction = 3 => movimento para direita  
|  ========================================================================================== */ 

void dfs(int x, int y) {
    if(arr[x][y] == '*') { // fim do problema, sucesso!
        ans = true;
        return;
    }
    // mudança de direção
    else if(arr[x][y] == '^') direction = 0;
    else if(arr[x][y] == 'v') direction = 1;
    else if(arr[x][y] == '<') direction = 2;
    else if(arr[x][y] == '>') direction = 3;
    
    // calculando nova posição
    int nx = x+dx[direction];
    int ny = y+dy[direction];
    
    // verificação se é uma posição válida ou então se já foi visitado
    if(nx < 0 or nx >= rows or ny < 0 or ny >= columns or vis[nx][ny]) return;
    
    vis[nx][ny] = true;
    dfs(nx,ny);
}

void solve() {
    // Entrada de dados
    cin >> columns >> rows;
    for(int i = 0; i < rows; i++) {
        cin >> arr[i];
    }

    vis[0][0] = true;
    dfs(0,0);
    
    // Saída
    if(ans) cout << "*\n";
    else cout << "!\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}