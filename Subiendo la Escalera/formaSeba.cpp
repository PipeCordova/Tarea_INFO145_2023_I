#include <iostream> // I/O
#include <vector> // Trabajamos con vectores
#include <algorithm> // Para utilizar el metodo find
#include <set> // Para usar set y su función insert()
#include <ctime> // Para cambiar la semilla y medir tiempo
#define FB 1 // 1 para mostrar la solución por Fuerza Bruta, 0 para no mostarla
#define PD 1 // 1 para mostrar la solución por Programación Dinámica, 0 para no mostarla
using namespace std; // Para usar cout y no std::cout

vector<int> creaPotencias(int p, int n);
void imprimeVector(vector<int> v);
void generaRotos(int cant, int n, vector<int>& rotos);
int formasPSC(int n, int k, vector<int>& B, vector<int>& rotos);
int formas(int n, int k, vector<int>& B, vector<int>& rotos, vector<int>& formaActual, vector<int>& ultimaForma);
long long formasPD(int n, int k, vector<int>& B, vector<int>& rotos);


int main(int argc, char* argv[]){
    if(argc != 4 || atoi(argv[3]) >= atoi(argv[1])){
        if(argc != 4){
            cout << "¡¡ERROR!! Tiene que compilar ./prog1 n p r\n n = numero de escalones\n p = base de la potencia de salto\n r = numero de escalones rotos" << endl;
        }else{// Obligamos que r < n --> Esto dice el enunciado. Se pueden pedir mas condiciones... 
            cout << "¡¡Debe cumplirse que r < n!!" << endl;
        }
        return EXIT_FAILURE; // --> Se termina el programa de manera inesperada.
    }

    // Para cambiar los numeros en cada ejecucion
    srand(time(0));

    // Declaración de Variables
    int n = atoi(argv[1]); // Numero de escalones
    int p = atoi(argv[2]); // Base de la potencia de salto
    int r = atoi(argv[3]); // Numero de escalones rotos
    vector<int> potencias = creaPotencias(p, n);
    int k = potencias.size();
    vector<int> rotos;
    generaRotos(r, n, rotos);
    vector<int> formaActual;
    vector<int> ultimaForma;
    vector<int> Aux(n-1);


    cout << "\n======================" << endl;
    cout << "|| DATOS DE ENTRADA ||" << endl;
    cout << "======================" << endl;
    cout << "n (escalones)\t= " << n << endl;
    cout << "p (base pot)\t= " << p << endl;
    cout << "Potencias\t= ";
    imprimeVector(potencias);
    cout << "r (rotos)\t= " << r << endl;
    cout << "Rotos\t\t= ";
    imprimeVector(rotos);
    if(FB){
        cout << "\n===============================" << endl;
        cout << "|| ALGORITMO DE FUERZA BRUTA ||" << endl;
        cout << "===============================" << endl;
        //cout << "Formas posibles PSC = " << formasPSC(n, k, potencias, rotos) << endl;
        clock_t t1 = clock();
        int f1 = formas(n,k,potencias,rotos,formaActual, ultimaForma);
        clock_t t2 = clock();
        double secs1 = static_cast<double>(t2-t1)/CLOCKS_PER_SEC;
        cout << "Formas posibles\t\t= " << f1 << endl;
        cout << "Tiempo de ejecución\t= " << secs1 << " segundos" << endl;
        // El vector ultima forma queda con los indices al reves, aplicamos reverse para se imprima bien la solución
        cout << "Forma mas corta\t\t= ";
        reverse(ultimaForma.begin(),ultimaForma.end());
        imprimeVector(ultimaForma);
    }

    if(PD){
        cout << "\n=============================================" << endl;
        cout << "|| ALGORITMO DE PROGRAMACION DINAMICA (PD) ||" << endl;
        cout << "=============================================" << endl;

        clock_t t3 = clock();
        long long f2 = formasPD(n, k, potencias, rotos) ;
        clock_t t4 = clock();
        double secs2 = static_cast<double>(t4-t3)/CLOCKS_PER_SEC;
        cout << "Formas posibles\t\t= " << f2 << endl;
        cout << "Tiempo de ejecución\t= " << secs2 << " segundos" << endl;
    }
    return EXIT_SUCCESS;
}

int formas(int n, int k, vector<int>& B, vector<int>& rotos, vector<int>& formaActual, vector<int>& ultimaForma) {
    if (n == 0) {
        // Se ha alcanzado el final de la escalera, almacenar la forma actual como la última forma
        ultimaForma = formaActual;
        return 1;
    }
    
    /*if (n < 0) {
        return 1;
    }*/
    
    int total = 0;
    for (int i = 0; i < k; i++) {
        if (n - B[i] >= 0 && find(rotos.begin(), rotos.end(), n) == rotos.end()) {
            // Agregar el índice actual a formaActual
            formaActual.push_back(n);
            total += formas(n - B[i], k, B, rotos, formaActual, ultimaForma);
            // Eliminar el último índice agregado para probar con el siguiente salto en la siguiente iteración
            formaActual.pop_back();
        }
    }
    return total;
}

// Hacer pseudocodigo de esta funcion
int formasPSC(int n, int k, vector<int>& B, vector<int>& rotos) {
    if (n == 0) {
        return 1;
    }
    
    int total = 0;
    for (int i = 0; i < k; i++) {
        if (n - B[i] >= 0 && find(rotos.begin(), rotos.end(), n) == rotos.end()) {
            total += formasPSC(n - B[i], k, B, rotos);
        }
    }
    
    return total;
}

long long formasPD(int n, int k, vector<int>& B, vector<int>& rotos) {
    vector<long long> aux(n + 1, 0);
    aux[0] = 1; // Caso base: hay una forma de subir una escalera de longitud 0
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            if (i - B[j] >= 0 && find(rotos.begin(), rotos.end(), i) == rotos.end()) {
                aux[i] += aux[i - B[j]];
            }
        }
    }
    
    return aux[n];
}

vector<int> creaPotencias(int p, int n) {
    vector<int> potencias;
    
    int pot = 1;
    while (pot <= n) {
        potencias.push_back(pot);
        pot *= p;
    }
    return potencias;
}

void generaRotos(int cant, int n, vector<int>& rotos){
    int cont = 0;
    set<int> numeros;
    int x;
    
    while( numeros.size() < cant ){
        x = rand() % n;
        numeros.insert(x);
    }
    
    rotos.assign(numeros.begin(), numeros.end());

}

void imprimeVector(vector<int> v){
    if(!v.empty()){
        for(int i = 0; i<v.size(); i++){
            cout << v[i] << " ";
        }
        cout << endl;
    }
    else{
        cout << "Se trató de imprimir un vector vacío!" << endl;
    }
}