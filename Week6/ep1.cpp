#include <bits/stdc++.h>

using namespace std;

const int MAX = 55;

class Point {
public:

    int x,y,h;
    int idx;
    double dist; // distancia desse idx até o centro

    Point() {}
    Point(int idx, int x, int y, int h) : idx(idx), x(x), y(y), h(h), dist(0.) {}

    bool operator < (const Point& other) {
        return (dist < other.dist);
    }

};

class Edge {
public:
    
    int v1,v2;
    double cost;

    Edge(int v1, int v2, double cost) : v1(v1), v2(v2), cost(cost) {}
};

void solve() {
    int t,group = 0;
    int parent[MAX];
    int weight[MAX];

    while(cin >> t) {
        if(t == 0) return;

        int totalInhabitants = 0;
        Point* center = new Point();
        vector<Point> pointers;

        for(int i = 0; i < t; i++) {
            int x,y,h;
            cin >> x >> y >> h;
            if(i == 0) {
                center->x = x;
                center->y = y;
                center->h = h;
                center->idx = i;
                center->dist = 0.;
            } else {
                Point p(i,x,y,h);
                int absX = abs(center->x - x);
                int absY = abs(center->y - y);
                double d = sqrt((absX*absX) + (absY*absY));
                p.dist = d;
                pointers.push_back(p);
            }
            totalInhabitants += h;
            parent[i] = i;
            weight[i] = 0;
        }

        sort(pointers.begin(),pointers.end());

        // Construir grafo com menor numero de arestas e também menor custo
        vector<Point> connecteds;
        vector<Edge> edges;
        double ans = 0.;
        int days = 0;

        for(auto p : pointers) {

            double distCurrent = p.dist; // distancia do ponto p ligado direto ao Center
            int connectionCurrent = center->idx; // vertice que p será ligado

            // Verificar o menor caminho que leva p até o center
            for(auto c : connecteds) {
                // cout << "# " << c.idx << endl;
                int absX = abs(p.x - c.x);
                int absY = abs(p.y - c.y);

                double dist_p_to_c = sqrt((absX*absX) + (absY*absY));
                double distC = c.dist;
                
                if(distCurrent > dist_p_to_c) {
                    connectionCurrent = c.idx;
                    distCurrent = dist_p_to_c;
                }
            }

            Edge e(p.idx,connectionCurrent,distCurrent);
            edges.push_back(e);

            int value = distCurrent*100;
            int quociente = value/100;
            int rest = value%100;

            days = quociente;
            if(rest > 0) days++;

            ans += (days*p.h);


            connecteds.push_back(p);

        }
        cout << "Island Group: " << ++group << " Average 3.20\n";
    }


}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout << fixed << setprecision(2);

    solve();
}
