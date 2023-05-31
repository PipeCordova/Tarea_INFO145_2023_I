/* Integrantes:
	- Felipe Córdova
	- Sebastián Montecinos
*/

/*
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    if (argc != 3) {
        cout << "¡¡ERROR!! Tiene que compilar ./prog1 r p" << endl;
        return EXIT_FAILURE;
    }
    cout << "¡¡Bienvenido Al Problema Subiendo La Escalera Hecha Por Fuerza Bruta!!" << endl;
    int r = atoi(argv[1]);
    int p = atoi(argv[2]);
    cout << "Ingreso r = " << r << " y p = " << p << endl;
    cout << "¡¡Fin Solución Fuerza Bruta!!" << endl;
    return EXIT_SUCCESS;
}
*/



// SOLUCION CASI


#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> encontrar_formas_posibles(int n, int p, int r, vector<int>& escalones_rotos, vector<int>& forma_actual) {
    vector<vector<int>> formas;
    
    if (forma_actual.back() == n) {
        formas.push_back(forma_actual);
        return formas;
    }
    
    for (int i = 0; i <= log(n) / log(p); i++) {
        int siguiente_escalón = forma_actual.back() + pow(p, i);
        
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
        vector<vector<int>> formas_subsecuentes = encontrar_formas_posibles(n, p, r, escalones_rotos, forma_actual);
        formas.insert(formas.end(), formas_subsecuentes.begin(), formas_subsecuentes.end());
        forma_actual.pop_back();
    }
    
    return formas;
}

int main() {
    int n = 10;  // Número de escalones
    int p = 2;   // Potencia de salto
    int r = 3;   // Número de escalones rotos
    
    vector<int> escalones_rotos = {4, 5, 8};  // Índices de los escalones rotos
    
    vector<int> forma_actual = {1};  // Comenzar en el escalón 1
    
    vector<vector<int>> formas = encontrar_formas_posibles(n, p, r, escalones_rotos, forma_actual);
    
    // Imprimir el número total de formas posibles
    cout << "Número total de formas posibles: " << formas.size() << endl;
    
    // Imprimir las formas posibles
    for (int i = 0; i < formas.size(); i++) {
        cout << "Forma " << i + 1 << ": ";
        for (int j = 0; j < formas[i].size(); j++) {
            cout << formas[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
