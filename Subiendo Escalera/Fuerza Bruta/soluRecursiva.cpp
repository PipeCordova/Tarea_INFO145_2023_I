/* Integrantes:
	- Felipe Cordova
	- Sebastian Montecinos
*/
#include <iostream> // I/O
#include <vector> // Trabajamos con vectores
#include <cmath> // Para usar la funcion pow y log
#include <cstdlib> // Para los numeros aleatorios
#include <algorithm> // Para utilizar el metodo find
#define TEST 1 // TEST = 0 <--> false, TEST = 1 <--> true

using namespace std;


vector<int> generarIndicesAleatorios(int n, int r);
void encontrarFormasPosibles(int pos, int n, int p, vector<int>& escalones_rotos, vector<int>& forma_actual, vector<vector<int>>& formas);
void imprimirEscalonesRotos(const vector<int>& escalonesRotos);
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
    vector<int> escalones_rotos = generarIndicesAleatorios(n, r);
    vector<vector<int>> formas;
    vector<int> forma_actual;
    encontrarFormasPosibles(0, n, p, escalones_rotos, forma_actual, formas);
    // Imprimir el numero total de formas posibles
    cout << "Número total de formas posibles: " << formas.size() << endl;
    if(TEST){
        imprimirEscalonesRotos(escalones_rotos);
        imprimirFormasPosibles(formas);
    }
    return EXIT_SUCCESS;
}

vector<int> generarIndicesAleatorios(int n, int r) {
    vector<int> escalones_rotos(r);
    srand(time(0));
    int k_aleatorio;
    for(int i = 0; i < r; i++){ // O(r)
        k_aleatorio = 1 + rand() % (n - 1);
        // El costo de este while en el peor caso es O(r-1)
        while(find(escalones_rotos.begin(), escalones_rotos.begin() + i, k_aleatorio) != escalones_rotos.begin() + i){
            k_aleatorio = 1 + rand() % (n - 1);
        }
        escalones_rotos[i] = k_aleatorio;
    } // --> Costo total de este ciclo anidado es O(r(r-1)) <--> O(r²)
    return escalones_rotos;
}


void encontrarFormasPosibles(int pos, int n, int p, vector<int>& escalones_rotos, vector<int>& forma_actual, vector<vector<int>>& formas) {
    if (pos == n) {
        formas.push_back(forma_actual);
        return;
    }
    
    for (int i = 0; i <= int(log(n) / log(p)); i++) {
        int siguiente_escalón = pos + pow(p, i);
        
        bool escalon_roto = false;
        for (int escalon : escalones_rotos) {
            if (siguiente_escalón == escalon) {
                escalon_roto = true;
                break;
            }
        }
        
        if (escalon_roto || siguiente_escalón > n) {
            continue;
        }
        
        forma_actual.push_back(siguiente_escalón);
        encontrarFormasPosibles(siguiente_escalón, n, p, escalones_rotos, forma_actual, formas);
        forma_actual.pop_back();
    }
}


void imprimirEscalonesRotos(const vector<int>& escalonesRotos) {
    cout << "Los escalones rotos son: ";
    for(int indice : escalonesRotos) {
        cout << indice << " ";
    }
    cout << "\n¡¡Tenga cuidado de pisarlos!!" << endl;
    return;
}

void imprimirFormasPosibles(const vector<vector<int>>& formas) {
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
