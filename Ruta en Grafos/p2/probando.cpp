#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

struct Node {
    int id;
    double dist;
    Node* anc;
    std::vector<std::pair<Node*, double>> neighbors;

    Node(int id) : id(id), dist(std::numeric_limits<double>::infinity()), anc(nullptr) {}
};

struct CompareDist {
    bool operator()(const Node* a, const Node* b) const {
        return a->dist > b->dist;
    }
};

void DIJKSTRA(std::vector<Node*>& graph, Node* start, std::vector<Node*>& ports) {
    std::priority_queue<Node*, std::vector<Node*>, CompareDist> pq;

    for (Node* node : graph) {
        node->dist = std::numeric_limits<double>::infinity();
        node->anc = nullptr;
    }

    start->dist = 0;
    pq.push(start);

    while (!pq.empty()) {
        Node* u = pq.top();
        pq.pop();

        for (const auto& neighbor : u->neighbors) {
            Node* v = neighbor.first;
            double weight = neighbor.second;

            if (v->dist > u->dist + weight) {
                v->dist = u->dist + weight;
                v->anc = u;
                pq.push(v);
            }
        }
    }

    // Imprimir las distancias mínimas y los recorridos a los puertos
    for (Node* port : ports) {
        std::cout << "Distancia mínima a Puerto " << port->id << ": " << port->dist << std::endl;

        // Obtener el recorrido
        std::stack<Node*> path;
        Node* curr = port;
        while (curr != nullptr) {
            path.push(curr);
            curr = curr->anc;
        }

        // Imprimir el recorrido
        std::cout << "Recorrido desde el nodo inicial al Puerto " << port->id << ": ";
        while (!path.empty()) {
            std::cout << path.top()->id;
            path.pop();
            if (!path.empty()) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl << std::endl;
    }
}

int main() {
    // Crear los nodos del grafo
    Node* nodeA = new Node(0);
    Node* nodeB = new Node(1);
    Node* nodeC = new Node(2);
    Node* nodeD = new Node(3);
    Node* nodeE = new Node(4);
    Node* nodeF = new Node(5);
    Node* nodeG = new Node(6);

    // Definir las conexiones y los pesos de las aristas
    nodeA->neighbors.emplace_back(nodeB, 5.0);
    nodeA->neighbors.emplace_back(nodeC, 3.0);
    nodeB->neighbors.emplace_back(nodeD, 2.0);
    nodeC->neighbors.emplace_back(nodeB, 1.0);
    nodeC->neighbors.emplace_back(nodeD, 6.0);
    nodeD->neighbors.emplace_back(nodeE, 4.0);
    nodeD->neighbors.emplace_back(nodeF, 2.0);
    nodeE->neighbors.emplace_back(nodeG, 3.0);
    nodeF->neighbors.emplace_back(nodeG, 1.0);

    // Crear el grafo
    std::vector<Node*> graph = {nodeA, nodeB, nodeC, nodeD, nodeE, nodeF, nodeG};

    // Definir los puertos
    std::vector<Node*> ports = {nodeE, nodeF, nodeG};

    // Nodo inicial
    Node* startNode = nodeA;

    // Ejecutar el algoritmo de Dijkstra
    DIJKSTRA(graph, startNode, ports);

    // Liberar memoria
    for (Node* node : graph) {
        delete node;
    }

    return 0;
}
