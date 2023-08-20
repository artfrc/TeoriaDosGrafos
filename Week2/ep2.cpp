// https://open.kattis.com/problems/runningmom

#include <bits/stdc++.h>
using namespace std;

map<string,int> mp;
vector<vector<int>> adj;
vector<bool> vis;
bool ans;

void dfs(int idx) {
    if(ans) return;
    
    for(auto neighbor : adj[idx]) {
        if(vis[neighbor]) {
            ans = true;
            return;
        }
        vis[neighbor] = true;
        dfs(neighbor);
    }
}

void solve() {
    int n;
    cin >> n;

    int nCitys = 0;
    vector<int> v;
    
    for(int i = 0; i < n; i++) {
        string city1, city2;
        cin >> city1 >> city2;

        if(mp.find(city1) == mp.end()) {
            mp[city1] = nCitys;
            nCitys++;
            adj.push_back(v);
            vis.push_back(false);
        }

        if(mp.find(city2) == mp.end()) {
            mp[city2] = nCitys;
            nCitys++;
            adj.push_back(v);
            vis.push_back(false);
        }

        int idxCity1 = mp[city1];
        int idxCity2 = mp[city2];

        adj[idxCity1].push_back(idxCity2);
    }

    string city;

    while(cin >> city) {
        if(mp.find(city) == mp.end()) {
            cout << city << " trapped\n";
        } else {
            int idxCity = mp[city];
            
            for(auto e : vis)
                e = false;

            vis[idxCity] = true;
            ans = false;

            dfs(idxCity);

            if(ans) cout << city << " safe\n";
            else cout << city << " trapped\n";
        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}