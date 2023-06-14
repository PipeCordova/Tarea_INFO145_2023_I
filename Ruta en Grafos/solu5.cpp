/* Este código realiza una búsqueda exhaustiva de todos los posibles caminos desde 
la ciudad capital s hasta la isla capital z. Para cada camino, calcula el costo total y mantiene 
un registro del costo mínimo encontrado hasta ahora. Sin embargo, este enfoque tiene una complejidad 
de tiempo de O(n!) y puede ser extremadamente lento para grandes valores de n.

El problema que has planteado es bastante complejo y, en general, no es práctico resolverlo con 
un algoritmo de fuerza bruta debido a su alta complejidad computacional. Sin embargo, aquí te 
proporciono un esbozo de cómo podría ser un algoritmo de fuerza bruta para este problema. 
Este código generará todas las permutaciones posibles de rutas y luego calculará el 
costo de cada una.*/




#include<bits/stdc++.h>
using namespace std;

#define INF 1e9

struct edge {
    int to, cost;
};

vector<vector<edge>> G; // Graph
vector<int> d; // Minimum cost

void bruteForce(int s, int z, vector<bool> &visited, int currCost, int &minCost) {
    if (s == z) {
        minCost = min(minCost, currCost);
        return;
    }

    visited[s] = true;

    for (auto &e : G[s]) {
        if (!visited[e.to]) {
            bruteForce(e.to, z, visited, currCost + e.cost, minCost);
        }
    }

    visited[s] = false;
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

    vector<bool> visited(n+m+2, false);
    int minCost = INF;
    bruteForce(s, z+n, visited, 0, minCost);

    cout << minCost << endl;

    return 0;
}