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
    return rand() % 11 - 5; // Genera un número aleatorio entre -5 y 5
}

vvi generarMatrizAdyacencia(int n) {
    vvi matriz(n, vi(n, -1));
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u != v) {
                int peso = rand() % 32 - 1; // Genera un número aleatorio entre -1 y 20
                matriz[u][v] = peso;
            }
        }
    }
    return matriz;
}

vi dijkstra(vvp& grafo, int source) {
    int n = grafo.size();
    vi dist(n, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int costo = pq.top().first;
        pq.pop();

        if (costo > dist[u]) {
            continue;
        }

        for (pii neighbor : grafo[u]) {
            int v = neighbor.first;
            int peso = neighbor.second;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

vi costoMinSZ(vvi& G, vvi& G_prima, int s, int z, int k, int m) {
    int n = G.size();

    // Construir grafo G en forma de lista de adyacencia
    vvp grafo(n);
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (G[u][v] != -1) {
                grafo[u].push_back({v, G[u][v]});
            }
        }
    }

    // Ejecutar Dijkstra en el grafo G para encontrar las rutas más económicas desde s a cada puerto pi
    vi puertos = dijkstra(grafo, s);

    // Construir grafo G' en forma de lista de adyacencia
    vvp grafo_prima(m);
    for (int u = 0; u < m; u++) {
        for (int v = 0; v < m; v++) {
            if (G_prima[u][v] != -1) {
                grafo_prima[u].push_back({v, G_prima[u][v]});
                grafo_prima[v].push_back({u, G_prima[u][v]});
            }
        }
    }

    // Ejecutar Dijkstra en el grafo G' para encontrar las rutas más económicas desde cada isla qj hasta z
    int t = log2(m);
    vi islas;
    for (int j = 0; j < t; j++) {
        vi dist = dijkstra(grafo_prima, j);
        islas.push_back(dist[z]);
    }
  
    int costoMin = INF;
    int besti = 0;
    int bestj = 0;

    // Calcular el costo total de la ruta desde s hasta z para cada combinación de puertos e islas
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= t; j++) {
            int costo = puertos[i] + costoBarco() + islas[j];
            if (costo <= costoMin) {
                costoMin = costo;
                besti = i;
                bestj = j;
            }
        }
    }

    return {costoMin, besti, bestj};
}

void imprimirMatrizAdyacencia(const vvi& matriz) {
    int n = matriz.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    srand(time(0)); // Inicializar semilla aleatoria

     if(argc != 4 || atoi(argv[2]) >= atoi(argv[1])){
        if(argc != 4){
            cout << "¡¡ERROR!! Tiene que compilar ./prog2 n k m\n n = nodos del continente\n k = puertos del continende (k<n)\n m = nodos del archipiélago\n" << endl;
        }else{ // Obligamos que k < n --> Esto dice el enunciado.
            cout << "¡¡Debe cumplirse que k < n!!" << endl;
        }
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int m = atoi(argv[3]);
    int s = 0; //Ciudad de partida
    int z = m; //Isla final

    // Generar matriz de adyacencia G aleatoriamente
    vvi G = generarMatrizAdyacencia(n);
    //imprimirMatrizAdyacencia(G);

    // Generar matriz de adyacencia G' aleatoriamente
    vvi G_prima = generarMatrizAdyacencia(m);
    //imprimirMatrizAdyacencia(G_prima);
    clock_t ti = clock();
    vi resultado = costoMinSZ(G, G_prima, s, z, k, m);
    clock_t tf = clock();
    double secs = static_cast<double>(tf-ti)/CLOCKS_PER_SEC;
    cout << "\nTiempo de ejecución \t= " << secs << " segundos." << endl;

    int costoMin = resultado[0];
    int besti = resultado[1];
    int bestj = resultado[2];

    cout << "Costo mínimo \t\t= " << costoMin << endl;
    cout << "Puerto óptimo \t\t= p" << besti << endl;
    cout << "Isla óptima \t\t= q" << bestj << endl;

    return 0;
}
