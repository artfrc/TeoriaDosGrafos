#include <bits/stdc++.h>
using namespace std;

const int MAX = 55;

class Edge {
public:
    int v1,v2;
    double cost;

    Edge(int v1, int v2, double cost) : v1(v1), v2(v2), cost(cost) {}

    bool operator < (const Edge& other) {
        return (cost < other.cost);
    }
};

class Pointer {
public:
    int idx;
    int x,y,h;

    Pointer(int idx, int x, int y, int h) : idx(idx), x(x), y(y), h(h) {}

};

vector<Edge> edges;
vector<Pointer> pointers;
int parent[MAX];
int weight[MAX];

int find(int idx, int parent[]) {
    if(parent[idx] == idx) return idx;
    return (parent[idx] = find(parent[idx],parent));
}

bool Union(Edge e, int parent[], int weight[]) {
    int parentV1 = find(e.v1, parent);
    int parentV2 = find(e.v2, parent);

    if(parentV1 == parentV2) return false;
    
    if(weight[parentV1] < weight[parentV2]) parent[parentV1] = parentV2;
    else if(weight[parentV1] > weight[parentV2]) parent[parentV2] = parentV1;
    else {
        parent[parentV1] = parentV2;
        weight[parentV2]++;
    }
    
    return true;
}

void solve() {
    int t, x, y, h;
    int count = 0;
    while(cin >> t) {
        if(t == 0) return;

        cin >> x >> y >> h; // lendo ponto central

        Pointer center(0,x,y,h);
        pointers.push_back(center);

        int totalPopulation = h;

        // Lendo o resto do input
        for(int i = 1; i < t; i++) {
            cin >> x >> y >> h;
            Pointer p(i,x,y,h);
            pointers.push_back(p);
            totalPopulation += h;
        }

        // Calcular arestas que geram um grafo completo
        for(int i = 0; i < t; i++) {
            parent[i] = i;
            weight[i] = 0;
            for(int j = i+1; j < t; j++) {
                // calcular distancia desses dois pontos
                int xi = pointers[i].x, yi = pointers[i].y;
                int xj = pointers[j].x, yj = pointers[j].y;
                
                int distanceX = abs(xi-xj);
                int distanceY = abs(yi-yj);

                double distancePointers = sqrt((distanceX*distanceX) + (distanceY*distanceY));
                Edge e(i,j,distancePointers);
                edges.push_back(e);
            }
        }

        sort(edges.begin(),edges.end());

        double ans = 0;

        for(auto e : edges) {
            if(Union(e,parent,weight)) {
                int v1 = e.v1;
                int v2 = e.v2;

                // calcular o tempo médio

                // se v1 ou v2 é o ponto central, entao devo pegar o numero de hab. do que não é ponto central
                if(v1 == 0 or v2 == 0) {
                    if(v1 == 0) {
                        ans += (ceil(e.cost)*pointers[v2].h);
                    } else {
                        ans += (ceil(e.cost)*pointers[v1].h);
                    }
                } else {
                    // se nenhum for ponto central, entao pegamos os habitantes do ponto mais longe do centro

                    // calcular distancia entre v1 e centro
                    int xv1 = pointers[v1].x, yv1 = pointers[v1].y; // v1
                    int xv2 = pointers[v2].x, yv2 = pointers[v2].y; // v2
                    int xCenter = pointers[0].x, yCenter = pointers[0].y; // centro

                    // Distancia entre V1 e Centro
                    int distanceXV1 = abs(xv1-xCenter);
                    int distanceYV1 = abs(yv1-yCenter);

                    double distanceV1ToCenter = sqrt((distanceXV1*distanceXV1) + (distanceYV1*distanceYV1));

                    // Distancia entre V2 e Centro
                    int distanceXV2 = abs(xv2-xCenter);
                    int distanceYV2 = abs(yv2-yCenter);

                    double distanceV2ToCenter = sqrt((distanceXV2*distanceXV2) + (distanceYV2*distanceYV2));

                    if(distanceV1ToCenter > distanceV2ToCenter) {
                        ans += (ceil(e.cost)*pointers[v1].h);
                    } else {
                        ans += (ceil(e.cost)*pointers[v2].h);
                    }
                }
            }
        }

        ans /= totalPopulation;
        ans = floor(ans * 100) / 100;

        cout << fixed << setprecision(2) <<  "Island Group: " << ++count << " Average " << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();
}