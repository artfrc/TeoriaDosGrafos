// https://open.kattis.com/problems/lostmap

#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;

const int MAX = 2678;

class Edge {
public:
    int v1,v2;
    lli cost;

    Edge(int v1, int v2, lli cost) : v1(v1), v2(v2), cost(cost) {}

    bool operator < (const Edge& other) {
        return (cost < other.cost);
    }
};

int parent[MAX];
int weight[MAX];
vector<Edge> ans;

int find(int idx) {
    if(parent[idx] == idx) return idx;
    return (parent[idx] = find(parent[idx]));
}

void Union(Edge e) {
    int v1 = e.v1;
    int v2 = e.v2;
    lli cost = e.cost;

    int parentV1 = find(v1);
    int parentV2 = find(v2);

    if(parentV1 != parentV2) {
        if(weight[v1] < weight[v2]) parent[parentV1] = parentV2;
        else if(weight[v1] > weight[v2]) parent[parentV2] = parentV1;
        else {
            parent[parentV1] = parentV2;
            weight[parentV2]++;
        }
        ans.push_back(e);
    }
}

void solve() {
    int n;
    cin >> n;
    
    vector<Edge> edges;

    for(int i = 0; i < n; i++) {
        parent[i] = i;
        weight[i] = 0;
        for(int j = 0; j < n; j++) {
            lli cost;
            cin >> cost;
            if(i == j) continue;
            Edge e(i,j,cost);
            edges.push_back(e);
        }
    }

    sort(edges.begin(),edges.end());

    for(auto e : edges) {
        Union(e);
    }

    for(auto e : ans) {
        cout << e.v1+1 << " " << e.v2+1 << "\n";
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}