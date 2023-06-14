/* Este es un problema complejo que implica la búsqueda del camino más corto en un grafo, 
con algunas condiciones adicionales. En este caso, se puede utilizar el algoritmo de Dijkstra para 
encontrar el camino más corto desde la capital continental hasta cada uno de los puertos, y 
luego desde las islas habilitadas hasta la capital del archipiélago. 

Aquí se muestra un esquema de cómo podría ser el código en C++. Tenga en cuenta que este es un 
esquema y puede necesitar ajustes y adiciones para adaptarse a su problema específico.

Este código implementa el algoritmo de Dijkstra para encontrar el camino más corto desde un nodo 
de inicio hasta todos los demás nodos en un grafo. El grafo se representa como una lista de adyacencia,
 donde cada nodo tiene una lista de sus vecinos y los costos para llegar a ellos. El algoritmo 
 utiliza una cola de prioridad para seleccionar siempre el nodo con la distancia más corta desde 
 el nodo de inicio que aún no se ha procesado.

Por favor, ten en cuenta que este código es un esquema y puede necesitar ajustes y adiciones para 
adaptarse a tu problema específico. Por ejemplo, necesitarás implementar la lógica para manejar las 
rutas marítimas y las bonificaciones de las islas. */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1000;
vector<pii> adj[MAXN]; // Lista de adyacencia para el grafo
int dist[MAXN]; // Distancias desde el nodo de inicio

void dijkstra(int start) {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    fill(dist, dist + MAXN, numeric_limits<int>::max());
    dist[start] = 0;
    q.push({0, start});

    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();

        if (d_v != dist[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (dist[v] + len < dist[to]) {
                dist[to] = dist[v] + len;
                q.push({dist[to], to});
            }
        }
    }
}

int main() {
    // Aquí debes llenar el grafo con tus datos
    // y luego llamar a dijkstra con el nodo de inicio

    dijkstra(6); // s es la capital continental

    // Ahora, dist[i] es la distancia más corta desde s hasta i
    // Puedes usar dist[i] para encontrar la ruta más económica hasta la capital del archipiélago

    return 0;
}