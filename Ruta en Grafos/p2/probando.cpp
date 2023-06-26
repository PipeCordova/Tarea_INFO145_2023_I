#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

struct Node {
    int id;
    int dist;
    Node* anc;
    vector<pair<Node*, int>> neighbors;

    Node(int id) : id(id), dist(std::numeric_limits<int>::max()), anc(nullptr) {}
};

struct CompareDist {
    bool operator()(const Node* a, const Node* b) const {
        return a->dist > b->dist;
    }
};

int costoBarco(Node* p, Node* q) {
    return rand() % 10;
}

void DIJKSTRA1(vector<Node*>& continente, Node* start, vector<Node*>& puertos) {
    priority_queue<Node*, std::vector<Node*>, CompareDist> pq;

    for (Node* node : continente) {
        node->dist = numeric_limits<int>::max();
        node->anc = nullptr;
    }

    start->dist = 0;
    pq.push(start);

    while (!pq.empty()) {
        Node* u = pq.top();
        pq.pop();

        for (const auto& neighbor : u->neighbors) {
            Node* v = neighbor.first;
            int weight = neighbor.second;

            if (v->dist > u->dist + weight) {
                v->dist = u->dist + weight;
                v->anc = u;
                pq.push(v);
            }
        }
    }

    // Imprimir las distancias mínimas y los recorridos a los puertos
    for (Node* puerto : puertos) {
        cout << "Distancia mínima a Puerto " << puerto->id << ": " << puerto->dist << endl;

        // Obtener el recorrido
        stack<Node*> path;
        Node* curr = puerto;
        while (curr != nullptr) {
            path.push(curr);
            curr = curr->anc;
        }

        // Imprimir el recorrido
        cout << "Recorrido desde el nodo inicial al Puerto " << puerto->id << ": ";
        while (!path.empty()) {
            cout << path.top()->id;
            path.pop();
            if (!path.empty()) {
                cout << " -> ";
            }
        }
        cout << endl << endl;
    }
}

void DIJKSTRA(vector<Node*>& continente, Node* start, vector<Node*>& puertos) {
    priority_queue<Node*, std::vector<Node*>, CompareDist> pq;

    for (Node* node : continente) {
        node->dist = numeric_limits<int>::max();
        node->anc = nullptr;
    }

    start->dist = 0;
    pq.push(start);

    int minDistance = numeric_limits<int>::max();
    int minCost = numeric_limits<int>::max();
    Node* minPuerto = nullptr;

    while (!pq.empty()) {
        Node* u = pq.top();
        pq.pop();

        for (const auto& neighbor : u->neighbors) {
            Node* v = neighbor.first;
            int weight = neighbor.second;

            if (v->dist > u->dist + weight) {
                v->dist = u->dist + weight;
                v->anc = u;
                pq.push(v);

                if (v->id == 4 || v->id == 5 || v->id == 6) { // Check if v is a port
                    if (v->dist < minDistance) {
                        minDistance = v->dist;
                        minCost = v->dist; // Actualizamos el costo mínimo
                        minPuerto = v;
                    }
                }
            }
        }
    }

    if (minPuerto != nullptr) {
        stack<Node*> path;
        Node* curr = minPuerto;
        while (curr != nullptr) {
            path.push(curr);
            curr = curr->anc;
        }

        cout << "Camino mínimo desde el nodo 0 al Puerto " << minPuerto->id << "= ";
        while (!path.empty()) {
            cout << path.top()->id;
            path.pop();
            if (!path.empty()) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Costo del camino mínimo: " << minCost << endl; // Mostramos el costo mínimo
    } else {
        cout << "No se encontró un puerto alcanzable desde el nodo 0." << endl;
    }
}

int main() {
    // Crear los nodos del continente
    Node* nodeA = new Node(0);
    Node* nodeB = new Node(1);
    Node* nodeC = new Node(2);
    Node* nodeD = new Node(3);
    Node* nodeE = new Node(4);
    Node* nodeF = new Node(5);
    Node* nodeG = new Node(6);

    // Definir las conexiones y los pesos de las aristas
    nodeA->neighbors.emplace_back(nodeB, 5);
    nodeA->neighbors.emplace_back(nodeC, 3);
    nodeB->neighbors.emplace_back(nodeD, 2);
    nodeC->neighbors.emplace_back(nodeB, 1);
    nodeC->neighbors.emplace_back(nodeD, 6);
    nodeD->neighbors.emplace_back(nodeE, 4);
    nodeD->neighbors.emplace_back(nodeF, 2);
    nodeE->neighbors.emplace_back(nodeG, 3);
    nodeF->neighbors.emplace_back(nodeG, 1);

    // Crear el continente
    vector<Node*> continente = {nodeA, nodeB, nodeC, nodeD, nodeE, nodeF, nodeG};

    // Definir los puertos
    vector<Node*> puertos = {nodeE, nodeF, nodeG};

    // Nodo inicial
    Node* startNode = nodeA;

    // Ejecutar el algoritmo de Dijkstra
    //este entrega los caminos mas economicos desde 0 hasta cada puerto
    DIJKSTRA1(continente, startNode, puertos);

    //este solo me da el camino mas economico desde 0 hasta un puerto
    DIJKSTRA(continente, startNode, puertos);

    // Liberar memoria
    for (Node* node : continente) {
        delete node;
    }

    return 0;
}

