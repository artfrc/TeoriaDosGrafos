#include <bits/stdc++.h>
using namespace std;

const int MAX = 123;

int columns, rows;
string arr[MAX];
bool vis[MAX][MAX] = {false};
bool ans = false;
int direction;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
//      ^ v < >

void dfs(int x, int y) {
    if(arr[x][y] == '*') {
        ans = true;
        return;
    } 
    else if(arr[x][y] == '^') direction = 0;
    else if(arr[x][y] == 'v') direction = 1;
    else if(arr[x][y] == '<') direction = 2;
    else if(arr[x][y] == '>') direction = 3;
    
    int nx = x+dx[direction];
    int ny = y+dy[direction];
    if(nx < 0 or nx >= rows or ny < 0 or ny >= columns or vis[nx][ny]) return;
    vis[nx][ny] = true;
    dfs(nx,ny);
}

void solve() {
    cin >> columns >> rows;
    for(int i = 0; i < rows; i++) {
        cin >> arr[i];
    }

    vis[0][0] = true;
    dfs(0,0);
    
    if(ans) cout << "*\n";
    else cout << "!\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}