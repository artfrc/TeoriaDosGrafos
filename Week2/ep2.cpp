// https://open.kattis.com/problems/runningmom

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5123 * 2;
map<string,int> mp;
vector<vector<int>> adj(MAXN);
vector<int> degree(MAXN,0);
bool vis[MAXN];
int nCitys = 0;

void solve() {
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        string city1, city2;
        cin >> city1 >> city2;

        if(mp.find(city1) == mp.end()) {
            mp[city1] = nCitys;
            nCitys++;
        }

        if(mp.find(city2) == mp.end()) {
            mp[city2] = nCitys;
            nCitys++;
        }

        int idxCity1 = mp[city1];
        int idxCity2 = mp[city2];

        adj[idxCity2].push_back(idxCity1);
        degree[idxCity1]++;
    }

    queue<int> q;

    for(int i = 0; i < nCitys; i++) {
        if(degree[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int idx = q.front();
        q.pop();
        for(auto e : adj[idx]) {
            degree[e]--;
            if(degree[e] == 0) q.push(e);
        }
    }

    string city;
    
    while(cin >> city) {
        int idxCity = mp[city];
        if(degree[idxCity] < 1) cout << city << " trapped\n"; 
        else cout << city << " safe\n";
    } 
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}