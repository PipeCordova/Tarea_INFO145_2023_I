/* Integrantes:
	- Felipe Córdova
	- Sebastián Montecinos
*/
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    if (argc != 4) {
        cout << "¡¡ERROR!! Tiene que compilar ./prog3 n k m" << endl;
        return EXIT_FAILURE;
    }
    cout << "¡¡Bienvenido Al Problema Ruta En Grafos Mediante Algoritmos Greedy!!" << endl;
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int m = atoi(argv[3]);
    cout << "Ingreso n = " << n << " y k = " << k << " y m = " << m << endl;
    cout << "¡¡Fin Solución!!" << endl;
    return EXIT_SUCCESS;
}