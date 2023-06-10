#include <iostream> // I/O
#include <vector> // Trabajamos con vectores
#include <cmath> // Para usar la funcion pow y log
#include <cstdlib> // Para los numeros aleatorios
#include <algorithm> // Para utilizar el metodo find
#include <ctime> // Para obtener la semilla de los números aleatorios
#define TEST 1 // TEST = 0 <--> false, TEST = 1 <--> true
using namespace std; // Para usar cout y no std::cout


// Declaracion de funciones
vector<int> generarEscalera(int n, int r);
vector<vector<int>> encontrarFormasPosibles(int n, int p, vector<int>& escalera);
void imprimirEscalera(const vector<int>& escalera, const int r);
void imprimirFormasPosibles(const vector<vector<int>>& formas);

int main(int argc, char* argv[]) {
    if (argc != 4 || atoi(argv[3]) >= atoi(argv[1])) {
        if (argc != 4) {
            cout << "¡¡ERROR!! Tiene que compilar ./prog1 n p r" << endl;
        } else {
            cout << "¡¡Debe cumplirse que r < n!!" << endl;
        }
        return EXIT_FAILURE;
    }
    cout << "¡¡Bienvenido Al Problema Subiendo La Escalera Hecho Por Fuerza Bruta!!" << endl;
    int n = atoi(argv[1]); // Numero de escalones
    int p = atoi(argv[2]); // Base de la potencia de salto
    int r = atoi(argv[3]); // Numero de escalones rotos
    vector<int> escalera = generarEscalera(n, r);
    vector<vector<int>> formas = encontrarFormasPosibles(n, p, escalera);
    if (TEST) {
        imprimirEscalera(escalera, r);
        imprimirFormasPosibles(formas);
    }
    cout << "¡¡Fin Fuerza Bruta!!" << endl;
    return EXIT_SUCCESS;
}

vector<int> generarEscalera(int n, int r) {
    vector<int> escalera(n, 1); // Inicializar el vector con 1 --> O(n)
    srand(time(0)); // Inicializar la semilla de números aleatorios
    int posicion;
    for (int i = 0; i < r; i++) {  // O(r)
        posicion = rand() % (n - 1); // Generar una posición aleatoria en el rango 0..n-1
        // Verificar si la posición ya ha sido asignada
        while (escalera[posicion] == 0) { // O(n) en el peor caso
            posicion = rand() % (n - 1); // Generar una nueva posición aleatoria
        }
        escalera[posicion] = 0; // Asignar cero en la posición aleatoria
    }
    // Costo total O(n + r*n) *CREO* 
    return escalera;
}


vector<vector<int>> encontrarFormasPosibles(int n, int p, vector<int>& escalera) {
    vector<vector<int>> formas; // Esta matriz retornará todos los posibles caminos
    
    vector<int> forma_actual;
    forma_actual.push_back(0); // Comenzamos en el escalón 0
    
    while (!forma_actual.empty()) {
        int pos_actual = forma_actual.back();
        forma_actual.pop_back();

        if (pos_actual >= n) {
            if (forma_actual.back() == n - 1) {
                forma_actual.pop_back(); // Eliminar el escalón final si se alcanzó
            }
            formas.push_back(forma_actual);
            continue;
        }

        for (int i = 0; i <= int(log(n) / log(p)); i++) {
            int siguiente_escalon = pos_actual + pow(p, i);

            if (siguiente_escalon > n - 1) {
                break; // Salir del bucle si se supera el número de escalones
            }

            if (escalera[siguiente_escalon] == 0) {
                continue; // Si el escalón está roto, pasar al siguiente
            }

            forma_actual.push_back(siguiente_escalon);
        }
    }

    return formas;
}



void imprimirEscalera(const vector<int>& escalera, const int r){
    cout << "La escalera con " << escalera.size() << " escalones y " << r << " rotos es: ";
    for(unsigned int indice : escalera) {
        cout << indice << " ";
    }
    cout << "\n¡¡Tenga cuidado de pisar los 0!!" << endl;
    return;
}

void imprimirFormasPosibles(const vector<vector<int>>& formas) {
    cout << "Numero total de formas posibles: " << formas.size() << endl;
    if(formas.size() == 0){
        cout << "No puede subir :c" << endl;
    }else{
        for(unsigned int i = 0; i < formas.size(); i++){
            cout << "Forma " << i + 1 << ": ";
            for(unsigned int j = 0; j < formas[i].size(); j++){
                cout << formas[i][j] << " ";
            }
            cout << endl;
        }
    }
    return;
}