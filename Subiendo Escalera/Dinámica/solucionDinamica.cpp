/* Integrantes:
	- Felipe Córdova
	- Sebastián Montecinos
*/
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    if (argc != 3) {
        cout << "¡¡ERROR!! Tiene que compilar ./prog2 r p" << endl;
        return EXIT_FAILURE;
    }
    cout << "¡¡Bienvenido Al Problema Subiendo La Escalera Hecho Por Programación Dinámica!!" << endl;
    int r = atoi(argv[1]);
    int p = atoi(argv[2]);
    cout << "Ingreso r = " << r << " y p = " << p << endl;
    cout << "¡¡Fin Solución Dinámica!!" << endl;
    return EXIT_SUCCESS;
}