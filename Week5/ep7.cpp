// https://open.kattis.com/problems/lostmap

#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;

const int MAX = 2678;

class Edge {
public:
    int v1,v2;
    lli cost;

    // Construtor
    Edge(int v1, int v2, lli cost) : v1(v1), v2(v2), cost(cost) {}

    // Método que será usado para ordenar o vector
    bool operator < (const Edge& other) {
        return (cost < other.cost);
    }
};

int parent[MAX];
int weight[MAX];
vector<Edge> ans;

// Procurar/atualizar o pai de um vertice
int find(int idx) {
    if(parent[idx] == idx) return idx;
    return (parent[idx] = find(parent[idx]));
}

// Unir duas componentes
void Union(Edge e) {
    int v1 = e.v1;
    int v2 = e.v2;
    lli cost = e.cost;

    int parentV1 = find(v1);
    int parentV2 = find(v2);

    // Se os vertices nao tem mesmo pai, ou seja, nao fazem parte da mesma componente, entao vamos uni-los
    if(parentV1 != parentV2) {
        // verificacoes para equilibrar a arvore
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

    // Leitura do input
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

    // Ordenando o vetor
    sort(edges.begin(),edges.end());

    // Gerando a MST
    for(auto e : edges) {
        Union(e);
    }

    // Output
    for(auto e : ans) {
        cout << e.v1+1 << " " << e.v2+1 << "\n";
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}