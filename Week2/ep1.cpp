// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=136

#include <bits/stdc++.h>
using namespace std;

void solve() {
    vector<string> v; // matriz de entrada
    string s; // para ler cada linha da matriz
    int nColumns = -1; // irá definir a maior palavra da matriz (numero maximo de colunas da matriz)
    int nLines = 0; // número de linhas da matriz, ou seja, numero de palavras lidas na entrada

    while(cin >> s) {
        if(s == "#") break;
        else {
            v.push_back(s);
            int Size = s.size();
            nColumns = max(Size,nColumns);
            nLines++;
        }
    }

    int letters[999] = {0}; // auxiliará para dizer se alguma letra já foi escolhida na resposta
    string ans = ""; // saída do problema (resposta)
    int line, column = 0;
    
    while(column < nColumns) { // percorrendo a matriz verticalmente
        line = 0;
        while(line < nLines) {
            if(column < v[line].size()) {
                if(!letters[v[line][column]]) {
                    ans += v[line][column];
                    letters[v[line][column]] = 1;
                }
            }
            line++;
        }
        column++;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}