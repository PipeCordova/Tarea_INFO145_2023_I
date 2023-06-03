/* Integrantes:
	- Felipe Cordova
	- Sebastian Montecinos
*/
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 4 || atoi(argv[3]) >= atoi(argv[1])){
        if(argc != 4){
            cout << "¡¡ERROR!! Tiene que compilar ./prog2 n p r" << endl;
        }else{ // Obligamos que r < n --> Esto dice el enunciado. Se pueden pedir mas condiciones... 
            cout << "¡¡Debe cumplirse que r < n!!" << endl;
        }
        return EXIT_FAILURE;
    }
    cout << "¡¡Bienvenido Al Problema Subiendo La Escalera Hecho Por Programacion Dinamica!!" << endl;
    int n = atoi(argv[1]); // Numero de escalones
    int p = atoi(argv[2]); // Potencia de salto
    int r = atoi(argv[3]); // Numero de escalones rotos
    cout << "¡¡Fin Solucion Dinamica!!" << endl;
    return EXIT_SUCCESS;
}
