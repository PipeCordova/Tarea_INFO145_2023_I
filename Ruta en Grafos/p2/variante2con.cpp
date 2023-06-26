#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <ctime>

using namespace std;

struct nodoGrafo {
    int id;
    vector<nodoGrafo*> adj;
};
typedef struct nodoGrafo Nodo;

/*unsigned int dijkstra_prime(vector<Node*>& G_prime, Node* s, Node* fin, vector<vector<int>>& cost_prime) {
    unsigned int m = G_prime.size();
    vector<int> dist(m, numeric_limits<int>::max());
    vector<bool> visited(m, false);
    dist[s->id] = 0;

    for (int i = 0; i < m - 1; ++i) {
        int u = -1;
        for (int j = 0; j < m; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }

        visited[u] = true;
        for (Node* v : G_prime[u]->adj) {
            unsigned alt = dist[u] + cost_prime[u][v->id];
            if (alt < dist[v->id])
                dist[v->id] = alt;
        }
    }

    return dist[fin->id];
}
*/

unsigned int dijkstra(vector<Nodo*>& G, Nodo* s, Nodo* fin, vector<vector<int>>& cost) {
    int n = G.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<bool> visited(n, false);
    dist[s->id] = 0;

    for (int i = 0; i < n - 1; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }

        visited[u] = true;
        for (Nodo* v : G[u]->adj) {
            unsigned int alt = dist[u] + cost[u][v->id];
            if (alt < dist[v->id])
                dist[v->id] = alt;
        }
    }

    return dist[fin->id];
}

int costoBarco(Nodo* p, Nodo* q) {
    return rand()%100;
}

pair<int, pair<int, int>> costoMinSZ(vector<Nodo*>& G, vector<vector<int>>& cost, vector<Nodo*>& G_prime, vector<vector<int>>& cost_prime, Nodo* s, Nodo* z) {
    vector<int> Puertos;
    for (Nodo* p : s->adj) {
        Puertos.push_back(dijkstra(G, s, p, cost));
    }
    vector<int> Islas;
    int m = G_prime.size();
    for (int j = 0; j < floor(log2(m)); ++j) {
        Nodo* q = G_prime[j];
        cout << "dijkstra(G_prime, q, z, cost_prime)= "<<dijkstra(G_prime, q, z, cost_prime) << endl;
        Islas.push_back(dijkstra(G_prime, q, z, cost_prime));
    }
    int costoMin = numeric_limits<int>::max();
    int besti = 0;
    int bestj = 0;
    for (int i = 0; i < Puertos.size(); ++i) {
        for (int j = 0; j < Islas.size(); ++j) {
            // El problema de los negativos viene de islas[j]
            int costo = Puertos[i] + costoBarco(s->adj[i], G_prime[j]) + Islas[j];
            if (costo <= costoMin) {
                costoMin = costo;
                besti = i;
                bestj = j;
            }
        }
    }
    return make_pair(costoMin, make_pair(besti, bestj));
}

int main() {
    srand(0);

    int max = numeric_limits<int>::max();
    // Crea los nodos del grafo
    Nodo* A = new Nodo{0};
    Nodo* B = new Nodo{1};
    Nodo* C = new Nodo{2};
    Nodo* D = new Nodo{3};
    Nodo* E = new Nodo{4};
    Nodo* F = new Nodo{5};

    // Crea las aristas del grafo
    A->adj = {B, C};
    B->adj = {A, C, D};
    C->adj = {A, B, D, E};
    D->adj = {B, C, E, F};
    E->adj = {C, D, F};
    F->adj = {D, E};

    // Define los costos de las aristas
    vector<vector<int>> cost = {
        {0, 1, 3, max, max, max},
        {1, 0, 1, 2, max, max},
        {3, 1, 0, 1, 5, max},
        {max, 2, 1, 0, 2, 4},
        {max, max, 5, 2, 0, 3},
        {max, max, max, 4, 3, 0}
    };

    // Llama a la función costoMinSZ para obtener el costo mínimo y las mejores opciones de nodos
    vector<Nodo*> G = {A, B, C, D, E, F};
    vector<Nodo*> G_prime = {D, E, F};
    vector<vector<int>> cost_prime = {
        {0, 2, max},
        {2, 0, 3},
        {max, 3, 0}
    };
    Nodo* s = A;
    Nodo* z = F;
    pair<int, pair<int, int>> result = costoMinSZ(G, cost, G_prime, cost_prime, s, z);

    // Imprime los resultados
    cout << "Costo mínimo: " << result.first << endl;
    cout << "Mejor puerto: " << s->adj[result.second.first]->id << endl;
    cout << "Mejor isla: " << G_prime[result.second.second]->id << endl;

    // Libera la memoria
    delete A;
    delete B;
    delete C;
    delete D;
    delete E;
    delete F;

    return 0;
}
