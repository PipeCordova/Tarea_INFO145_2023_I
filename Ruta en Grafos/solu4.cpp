/* Este es un problema complejo que implica la búsqueda del camino más corto en un grafo, 
con algunas condiciones adicionales. Podemos resolverlo utilizando el algoritmo de Dijkstra 
para encontrar el camino más corto entre dos nodos en un grafo. Sin embargo, debido a la complejidad
del problema, el código puede ser bastante largo y complicado. Aquí hay un esbozo de cómo podrías 
abordarlo: 
Este código es solo un esbozo y puede que necesites ajustarlo para que se ajuste a tus necesidades 
específicas. Además, este código asume que los nodos están numerados de 0 a n-1 para las ciudades 
y de n a n+m-1 para las islas. También asume que los puertos y las islas que pueden recibir barcos 
están numerados de acuerdo con su correspondiente ciudad o isla. Por último, este código no toma en 
cuenta las bonificaciones que algunas islas pueden ofrecer a los barcos, por lo que es posible que 
necesites modificar el código para que tome en cuenta estas bonificaciones. */


#include<bits/stdc++.h>
using namespace std;

#define INF 1e9

struct edge {
    int to, cost;
};

typedef pair<int, int> P; // Pair of minimum cost and node number

vector<vector<edge>> G; // Graph
vector<int> d; // Minimum cost

void dijkstra(int s) {
    priority_queue<P, vector<P>, greater<P>> que;
    fill(d.begin(), d.end(), INF);
    d[s] = 0;
    que.push(P(0, s));

    while (!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (auto &e : G[v]) {
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}

int main() {
    int n, m, k, s, z;
    cin >> n >> m >> k >> s >> z;
    G.resize(n+m+2);
    d.resize(n+m+2);

    // Read the edges of the continental graph
    for (int i = 0; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w}); // If the graph is undirected
    }

    // Read the edges of the island graph
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        G[x+n].push_back({y+n, w});
        G[y+n].push_back({x+n, w}); // If the graph is undirected
    }

    // Read the edges between the ports and the islands
    for (int i = 0; i < k; i++) {
        int p, q, w;
        cin >> p >> q >> w;
        G[p].push_back({q+n, w});
    }

    dijkstra(s);

    cout << d[z+n] << endl;

    return 0;
}