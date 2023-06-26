// Esto es una implementacion del algoritmo de Dijsktra.

#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

struct Node {
    int id;
    int dist;
    Node* anc;
    vector<Node*> adj;
};

struct CompareDist {
    bool operator()(Node* const& n1, Node* const& n2) {
        return n1->dist > n2->dist;
    }
};

void dijkstra(vector<Node*>& G, Node* s, vector<vector<int>>& cost) {
    for (Node* u : G) {
        u->dist = numeric_limits<int>::max();
        u->anc = nullptr;
    }
    s->dist = 0;
    priority_queue<Node*, vector<Node*>, CompareDist> Q(G.begin(), G.end());
    vector<Node*> S;
    while (!Q.empty()) {
        Node* u = Q.top();
        Q.pop();
        S.push_back(u);
        for (Node* v : u->adj) {
            int newDist = u->dist + cost[u->id][v->id];
            if (v->dist > newDist) {
                v->dist = newDist;
                v->anc = u;
                // Actualizar la cola de prioridad
                make_heap(const_cast<Node**>(&Q.top()), const_cast<Node**>(&Q.top()) + Q.size(), CompareDist());
            }
        }
    }
}
