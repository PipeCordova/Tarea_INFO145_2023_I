#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<pii>> vvp;

const int INF = numeric_limits<int>::max();


int costoBarco() {
    return 1 + rand() % 10; // Genera un número aleatorio entre 1 y 10
}
/*
vvi generarMatrizAdyacencia(int n) {
    vvi matrix(n, vi(n, -1));
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u != v) {
                int weight = rand() % 21; // Genera un número aleatorio entre 0 y 20
                matrix[u][v] = weight;
            }
        }
    }
    return matrix;
}
*/

vvi generarMatrizAdyacencia(int n) {
    vvi matrix(n, vi(n, -1));
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u != v) {
                int weight = rand() % 22 - 1; // Genera un número aleatorio entre -1 y 20
                matrix[u][v] = weight;
            }
        }
    }
    return matrix;
}

vi dijkstra(vvp& graph, int source) {
    int n = graph.size();
    vi dist(n, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if (cost > dist[u]) {
            continue;
        }

        for (pii neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

vector<int> costoMinSZ(vector<vector<int>>& G, vector<vector<int>>& G_prime, int s, int z, int k, int m) {
    int n = G.size();

    // Construir grafo G en forma de lista de adyacencia
    vvp graph(n);
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (G[u][v] != -1) {
                graph[u].push_back({v, G[u][v]});
            }
        }
    }

    // Ejecutar Dijkstra en el grafo G para encontrar las rutas más económicas desde s a cada puerto pi
    vi ports = dijkstra(graph, s);

    // Construir grafo G' en forma de lista de adyacencia
    vvp graph_prime(m);
    for (int u = 0; u < m; ++u) {
        for (int v = 0; v < m; ++v) {
            if (G_prime[u][v] != -1) {
                graph_prime[u].push_back({v, G_prime[u][v]});
                graph_prime[v].push_back({u, G_prime[u][v]});
            }
        }
    }

    // Ejecutar Dijkstra en el grafo G' para encontrar las rutas más económicas desde cada isla qj hasta z
    int t = log2(m);
    vector<int> islands;
    for (int j = 0; j <= t; ++j) {
        vi dist = dijkstra(graph_prime, j);
        islands.push_back(dist[z]);
    }

    int costoMin = numeric_limits<int>::max();
    int besti = 0;
    int bestj = 0;

    // Calcular el costo total de la ruta desde s hasta z para cada combinación de puertos e islas
    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j <= t; ++j) {
            int costo = ports[i] + costoBarco() + islands[j];

            if (costo <= costoMin) {
                costoMin = costo;
                besti = i;
                bestj = j;
            }
        }
    }

    return {costoMin, besti, bestj};
}

void imprimirMatrizAdyacencia(const vvi& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    srand(time(nullptr)); // Inicializar semilla aleatoria

    int n = 4; // Número de ciudades
    int m = 3; // Número de islas habilitadas
    int s = 0; // Ciudad de partida
    int z = 2; // Isla de llegada
    int k = 2; // Número de puertos

    // Generar matriz de adyacencia G aleatoriamente
    vvi G = generarMatrizAdyacencia(n);
    imprimirMatrizAdyacencia(G);

    // Generar matriz de adyacencia G' aleatoriamente
    vvi G_prime = generarMatrizAdyacencia(m);
    imprimirMatrizAdyacencia(G_prime);

    vector<int> resultado = costoMinSZ(G, G_prime, s, z, k, m);
    int costoMin = resultado[0];
    int besti = resultado[1];
    int bestj = resultado[2];

    cout << "Costo mínimo: " << costoMin << endl;
    cout << "Puerto óptimo: p" << besti << endl;
    cout << "Isla óptima: q" << bestj << endl;

    return 0;
}
