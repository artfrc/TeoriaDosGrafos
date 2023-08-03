#include <bits/stdc++.h>
using namespace std;

const int MAX = 123;

string arr[MAX];
bool vis[MAX][MAX];
int ans, rows, columns;
int dx[] = {-1,-1,-1,1, 1,1, 0,0};
int dy[] = { 0,-1, 1,0,-1,1,-1,1};
// cima, dig. cima esq, dig. cima dir, bx, dig. bx esq, dig. bx dir, esq, dir

void dfs(int x, int y) {
    for(int i = 0; i < 8; i++) {
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx < 0 or nx >= rows or ny < 0 or ny >= columns or arr[nx][ny] != '@' or vis[nx][ny]) continue;
        vis[nx][ny] = true;
        dfs(nx,ny);
    }
}

void solve() {
    while(cin >> rows >> columns) {
        if(rows == 0) return;

        memset(vis,false,sizeof(vis));
        ans = 0;

        for(int i = 0; i < rows; i++) {
            cin >> arr[i];
        }

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                if(arr[i][j] == '@' and !vis[i][j]) {
                    ans++;
                    vis[i][j] = true;
                    dfs(i,j);
                }
            }
        }
        cout << ans << "\n";
    }
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}