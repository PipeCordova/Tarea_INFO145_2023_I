#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

struct Node {
    int id;
    vector<Node*> adj;
};

int dijkstra(vector<Node*>& G, Node* s, Node* z, vector<vector<int>>& cost) {
    // Implementa aquí tu función Dijkstra y devuelve el costo mínimo desde s a z
}

int costoBarco(Node* p, Node* q) {
    // Implementa aquí tu función costoBarco y devuelve el costo de ir de p a q
}

pair<int, pair<int, int>> costoMinSZ(vector<Node*>& G, vector<vector<int>>& cost, vector<Node*>& G_prime, vector<vector<int>>& cost_prime, Node* s, Node* z) {
    vector<int> Puertos;
    for (Node* p : s->adj) {
        Puertos.push_back(dijkstra(G, s, p, cost));
    }
    vector<int> Islas;
    int m = G_prime.size();
    for (int j = 0; j < log2(m); ++j) {
        Node* q = G_prime[j];
        Islas.push_back(dijkstra(G_prime, q, z, cost_prime));
    }
    int costoMin = numeric_limits<int>::max();
    int besti = 0;
    int bestj = 0;
    for (int i = 0; i < Puertos.size(); ++i) {
        for (int j = 0; j < Islas.size(); ++j) {
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