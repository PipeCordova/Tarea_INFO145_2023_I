/* Integrantes:
	- Felipe Cordova
	- Sebastian Montecinos
*/
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 4 || atoi(argv[2]) >= atoi(argv[1])){
        if(argc != 4){
            cout << "¡¡ERROR!! Tiene que compilar ./prog3 n k m" << endl;
        }else{ // Obligamos que k < n --> Esto dice el enunciado.
            cout << "¡¡Debe cumplirse que k < n!!" << endl;
        }
        return EXIT_FAILURE;
    }
    cout << "¡¡Bienvenido Al Problema Ruta En Grafos Mediante Algoritmos Greedy!!" << endl;
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int m = atoi(argv[3]);
    cout << "¡¡Fin Solucion!!" << endl;
    return EXIT_SUCCESS;
}
