#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

struct Node {
    int id;
    vector<Node*> adj;
};

int dijkstra(vector<Node*>& G, Node* s, Node* z, vector<vector<int>>& cost);

int costoBarco(Node* pi, Node* qj);

vector<int> costoMinSZ(vector<Node*>& G, vector<vector<int>>& cost, vector<Node*>& G_prime, vector<vector<int>>& cost_prime, Node* s, Node* z) {
    vector<int> Puertos;
    for (Node* p : s->adj) {
        Puertos.push_back(dijkstra(G, s, p, cost));
    }
    vector<int> islas;
    for (int i = 1; i <= log2(G_prime.size()); ++i) {
        Node* qj = G_prime[i];
        islas.push_back(dijkstra(G_prime, qj, z, cost_prime));
    }
    int costoMin = numeric_limits<int>::max();
    int besti = 0;
    int bestj = 0;
    for (int i = 0; i < Puertos.size(); ++i) {
        for (int j = 0; j <= floor(log2(G_prime.size())); ++j) {
            int costo = Puertos[i] + costoBarco(G[i], G_prime[j]) + islas[j];
            if (costo <= costoMin) {
                costoMin = costo;
                besti = i;
                bestj = j;
            }
        }
    }
    return {costoMin, besti, bestj};
}