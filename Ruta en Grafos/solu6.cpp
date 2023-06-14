/* Por favor, ten en cuenta que este código es solo un esbozo y puede que necesites 
ajustarlo para que se ajuste a tus necesidades específicas. Además, este código no toma 
en cuenta las bonificaciones que algunas islas pueden ofrecer a los barcos, por lo que es 
posible que necesites modificar el código para que tome en cuenta estas bonificaciones.

Este código genera todas las permutaciones posibles de rutas y luego calcula el costo de cada una. 
El costo mínimo se actualiza cada vez que se encuentra un costo más bajo. Al final, 
el costo mínimo se imprime en la consola. */

#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

struct edge {
    int to, cost;
};

vector<vector<edge>> G; // Graph

int bruteForce(int s, int z, vector<int> nodes) {
    int minCost = INF;
    do {
        int currentCost = 0;
        int currentNode = s;
        for (int node : nodes) {
            bool found = false;
            for (edge e : G[currentNode]) {
                if (e.to == node) {
                    currentCost += e.cost;
                    currentNode = node;
                    found = true;
                    break;
                }
            }
            if (!found) {
                currentCost = INF;
                break;
            }
        }
        minCost = min(minCost, currentCost);
    } while (next_permutation(nodes.begin(), nodes.end()));
    return minCost;
}

int main() {
    int n, m, k, s, z;
    cin >> n >> m >> k >> s >> z;
    G.resize(n+m+2);

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

    vector<int> nodes(n+m);
    iota(nodes.begin(), nodes.end(), 0);

    cout << bruteForce(s, z+n, nodes) << endl;

    return 0;
}