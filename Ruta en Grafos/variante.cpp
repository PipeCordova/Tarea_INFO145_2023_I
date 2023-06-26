#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <ctime>

using namespace std;

struct Node {
    int id;
    vector<Node*> adj;
};

// Declaracion de funciones
int dijkstra(vector<Node*>& G, Node* s, Node* fin, vector<vector<int>>& cost);
int costoBarco(Node* p, Node* q);
// Ojo que esto es una funcion, debido a su largo se hizo salto de linea.
pair<int, pair<int, int>> costoMinSZ(vector<Node*>& G, 
vector<vector<int>>& cost, vector<Node*>& G_prime, vector<vector<int>>& cost_prime, Node* s, Node* z);


// Inicio programa
int main() {
    srand(time(0));

    int max = numeric_limits<int>::max();
    // Crea los nodos del grafo
    Node* A = new Node{0};
    Node* B = new Node{1};
    Node* C = new Node{2};
    Node* D = new Node{3};
    Node* E = new Node{4};
    Node* F = new Node{5};

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
    vector<Node*> G = {A, B, C, D, E, F};
    vector<Node*> G_prime = {D, E, F};
    vector<vector<int>> cost_prime = {
        {0, 2, max},
        {2, 0, 3},
        {max, 3, 0}
    };
    Node* s = A;
    Node* z = F;
    pair<int, pair<int, int>> result = costoMinSZ(G, cost, G_prime, cost_prime, s, z);

    // Imprime los resultados
    cout << "Costo mínimo: " << result.first << endl;
    cout << "Mejor puerto: " << s->adj[result.second.first]->id << endl;
    cout << "Mejor isla: " << G_prime[result.second.second]->id << endl;

    // Liberar la memoria
    delete A;
    delete B;
    delete C;
    delete D;
    delete E;
    delete F;

    return 0;
}

int dijkstra(vector<Node*>& G, Node* s, Node* fin, vector<vector<int>>& cost) {
    int n = G.size();
    vector<int> dist(n, -1);
    vector<bool> visited(n, false);
    dist[s->id] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }

        visited[u] = true;
        for (Node* v : G[u]->adj) {
            int alt = dist[u] + cost[u][v->id];
            if (alt < dist[v->id])
                dist[v->id] = alt;
        }
    }

    return dist[fin->id];
}


int costoBarco(Node* p, Node* q) {
    //int x = rand()%10;
    //cout << p->id <<"--"<<x<<"->"<<q->id << endl;
    return rand()%10;
}

pair<int, pair<int, int>> costoMinSZ(vector<Node*>& G, vector<vector<int>>& cost, vector<Node*>& G_prime, vector<vector<int>>& cost_prime, Node* s, Node* z) {
    vector<int> Puertos;
    for (Node* p : s->adj) {
        Puertos.push_back(dijkstra(G, s, p, cost));
    }
    vector<long long int> Islas;
    int m = G_prime.size();
    for (int j = 0; j < floor(log2(m)); j++) {
        Node* q = G_prime[j];
        //cout << "dijkstra(G_prime, q, z, cost_prime)= "<<dijkstra(G_prime, q, z, cost_prime) << endl;
        Islas.push_back(dijkstra(G_prime, q, z, cost_prime));
    }
    //cout << "Islas size= "<<Islas.size()<<endl;
    //cout << "islas[0]= "<<Islas[0]<<endl;  --> Aqui esta el error!!, da overflow.
    
    int costoMin = numeric_limits<int>::max();
    int besti = 0;
    int bestj = 0;
    for (int i = 0; i < Puertos.size(); i++) {
        for (int j = 0; j < Islas.size(); j++) {
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
