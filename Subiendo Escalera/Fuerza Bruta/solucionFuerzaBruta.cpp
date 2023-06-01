/* Integrantes:
	- Felipe Córdova
	- Sebastián Montecinos
*/

#include <iostream> 
#include <vector> // Trabajamos con vectores
#include <cmath> // Para usar la funcion pow y log
#include <stdlib.h> // Para los numeros randoms
#include <algorithm> // Para utilizar la funcion sort 

using namespace std;

vector<vector<int>> encontrarFormasPosibles(int n, int p, vector<int>& escalones_rotos) {
    vector<vector<int>> formas;
    
    vector<int> forma_inicial;
    
    vector<vector<int>> formas_actuales;
    formas_actuales.push_back(forma_inicial);
    
    while(!formas_actuales.empty()){
        vector<int> forma_actual = formas_actuales.back();
        formas_actuales.pop_back();
        
        int pos_actual;
        if(forma_actual.empty()){
            pos_actual = 0;
        }else{
            pos_actual = forma_actual.back();
        }
        
        if(pos_actual == n){
            if(!forma_actual.empty() && forma_actual[0] == 0){
                forma_actual.erase(forma_actual.begin()); // Eliminar el 0 al comienzo
            }
            formas.push_back(forma_actual);
            continue; // si estas condiciones se cumplen se pasa a la sgte iteracion
        }
        
        // log(n) / log(n) nos da el numero maximo de saltos.
        for(int i = 0; i <= (log(n) / log(p)); i++){
            int siguiente_escalon = pos_actual + pow(p, i);
            
            bool escalon_roto = false;
            for(int escalon : escalones_rotos){
                if(siguiente_escalon == escalon){
                    escalon_roto = true;
                    break;
                }
            }
            
            if(escalon_roto == true || siguiente_escalon > n){
                continue; // si estas condiciones se cumplen se pasa a la sgte iteracion
            }
            
            vector<int> nueva_forma = forma_actual;
            nueva_forma.push_back(siguiente_escalon);
            formas_actuales.push_back(nueva_forma);
        }
    }
    
    return formas;
}

int main() {
    cout << "¡¡Bienvenido Al Problema Subiendo La Escalera Hecho Por Fuerza Bruta!!" << endl;
    int n;  // Numero de escalones
    int p;   // Potencia de salto
    int r;   // Numero de escalones rotos

    // Pidiendo al usuario los numeros correspondientes.
    cout << "Ingrese el numero de escalones n = ";
    cin >> n;
    cout << "Ingrese el la potencia de salto p = ";
    cin >> p;
    cout << "Ingrese el numero de escalones rotos r = ";
    cin >> r;

    // Se puede pedir muchas condiciones, ejemplo: n,p,r > 1, solo pondremos la que sale en el enunciado.
    if(r >= n){
        cout << "Debe cumplirse que r < n !!" << endl;
        return EXIT_FAILURE; // Se termina el programa de manera anormal.
    }
    
    vector<int> escalones_rotos(r);  // vector para almacenar los indices de los escalones rotos

    // Inicializar la semilla con el tiempo actual, asi tenemos randoms distintos en cada ejecucion
    srand(time(0));

    // Aqui se crean los indices aleatorios de los escalones rotos. Desde 1 hasta n-1
    int k_aleatorio;
    for (int i = 0; i < r; i++) {
        k_aleatorio = 1 + rand() % (n - 1);

        // verificando que siempre se agregen indices distintos
        while(find(escalones_rotos.begin(), escalones_rotos.begin() + i, k_aleatorio) != escalones_rotos.begin() + i) {
            k_aleatorio = 1 + rand() % (n - 1);
        }

        escalones_rotos[i] = k_aleatorio;
    }

    
    sort(escalones_rotos.begin(), escalones_rotos.end()); // Ordenar el vector en orden creciente con los indices

    // Mostrar el vector de escalones_rotos
    cout << "Los escalones rotos son: ";
    for (int indice : escalones_rotos) {
        cout << indice << " ";
    }
    cout << "\n¡¡Tenga cuidado!!" << endl;

    vector<vector<int>> formas = encontrarFormasPosibles(n, p, escalones_rotos);
    
    // Imprimir el número total de formas posibles
    cout << "Numero total de formas posibles: " << formas.size() << endl;

    if(formas.size() == 0){
        return EXIT_SUCCESS;
    // si hay 0 formas posibles, terminamos el programa, asi evitamos perder tiempo imprimiendo nada
    }else{
        // Imprimir las formas posibles
        for(unsigned int i = 0; i < formas.size(); i++) {
            cout << "Forma " << i + 1 << ": ";
            for(unsigned int j = 0; j < formas[i].size(); j++) {
                cout << formas[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << "¡¡Fin Fuerza Bruta!!" << endl;
    return EXIT_SUCCESS;
}


