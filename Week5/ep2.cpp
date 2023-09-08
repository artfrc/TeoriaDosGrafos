// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=2678

#include <bits/stdc++.h>
using namespace std;

const int MAX = 212345;

typedef long long int lli;

// classe Aresta
class Edge {
public:

    int v1, v2; // vertice 1, vertice 2
    lli cost;

    // Construtor da classe
    Edge(int v1, int v2, lli cost) : v1(v1), v2(v2), cost(cost) {}

    // Método que o sort irá usar para ordenar
    bool operator < (const Edge& other) {
        return (cost < other.cost);
    }
};

// Procurar o pai de um vertice
int find(int idx, int parent[]) {
    if(parent[idx] == idx) return idx;
    return parent[idx] = find(parent[idx],parent);
}

// Juntar duas componentes
void Union(Edge e, int parent[], lli weight[]) {
    int parentV1 = find(e.v1,parent);
    int parentV2 = find(e.v2,parent);

    if(parentV1 != parentV2) {
        if(weight[parentV1] < weight[parentV2]) parent[parentV1] = parentV2;
        else if(weight[parentV1] > weight[parentV2]) parent[parentV2] = parentV1;
        else {
            parent[parentV1] = parentV2;
            weight[parentV2]++;
        }
    }
}

void solve() {
    int n,m;
    while(cin >> n >> m) {
        if(n == 0 and m == 0) return;

        vector<Edge> edges; // array das arestas
        lli totalCost = 0; // custo total para iluminar as estradas
        lli minCost = 0; // custo minimo

        // Leitura do input
        for(int i = 0; i < m; i++) {
            int v1,v2;
            lli cost;
            cin >> v1 >> v2 >> cost;
            Edge e(v1,v2,cost);
            edges.push_back(e);
            totalCost += cost;
        }

        sort(edges.begin(),edges.end()); // ordenando as arestas

        int parent[MAX]; // armazenar o pai de cada vtx para separar as componentes

        // inicio com cada vertice sendo seu proprio pai
        for(int i = 0; i < n; i++)
            parent[i] = i;

        lli weight[MAX] = {0}; // ira auxiliar para equilibrar as componentes

        // achando minimum spanning tree
        for(auto edg : edges) {
            int v1 = edg.v1;
            int v2 = edg.v2;
            lli cost = edg.cost;

            if(find(v1,parent) != find(v2,parent)) {
                minCost += cost;
                Union(edg,parent,weight);
            }
        }

        // Output
        cout << totalCost-minCost << "\n";

    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}