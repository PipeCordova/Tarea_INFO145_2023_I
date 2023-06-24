#include <iostream> // I/O
#include <vector> // Trabajamos con vectores
#include <algorithm> // Para utilizar el metodo find
#include <set> // Para usar set y su función insert()
#include <ctime> // Para cambiar la semilla y medir tiempo
#include <climits> // Para usar LLONG_MAX
#define FB 0 // 1 para mostrar la solución por Fuerza Bruta, 0 para no mostarla
#define PD 1 // 1 para mostrar la solución por Programación Dinámica, 0 para no mostarla
using namespace std; // Para usar cout y no std::cout

// Declaración de funciones a utilizar
void imprimeVector(vector<int> v);
void generaRotos(int cant, int n, vector<int>& rotos);
unsigned long long int formasPD(int n, int k, vector<int>& B, vector<int>& rotos);
int formasFB(int n, int k, vector<int>& B, vector<int>& rotos);
vector<int> creaPotencias(int p, int n);
vector<int> formaMasCortaPD(int n, int k, vector<int>& B, vector<int>& rotos);

// Inicio del programa
int main(int argc, char* argv[]){
    if(argc != 4 || atoi(argv[3]) >= atoi(argv[1])){
        if(argc != 4){
            cout << "¡¡ERROR!! Tiene que compilar ./prog1 n p r\n n = numero de escalones\n p = base de la potencia de salto\n r = numero de escalones rotos" << endl;
        }else{// Obligamos que r < n --> Esto dice el enunciado. Se pueden pedir mas condiciones... 
            cout << "¡¡Debe cumplirse que r < n!!" << endl;
        }
        exit(EXIT_FAILURE); // --> Se termina el programa de manera inesperada.
    }

    srand(time(0)); // Para cambiar los números random en cada ejecución

    // Declaración de Variables
    int n = atoi(argv[1]); // Número de escalones
    int p = atoi(argv[2]); // Base de la potencia de salto
    int r = atoi(argv[3]); // Número de escalones rotos
    vector<int> potencias = creaPotencias(p, n);
    int k = potencias.size(); // Cantidad de potencias de p <= n

    vector<int> rotos;
    generaRotos(r, n, rotos);

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
        cout << "\n====================================" << endl;
        cout << "|| ALGORITMO DE FUERZA BRUTA (FB) ||" << endl;
        cout << "====================================" << endl;
        clock_t t1 = clock();
        cout << "Formas posibles\t\t= " << formasFB(n,k,potencias,rotos) << endl;
        clock_t t2 = clock();
        double secs1 = static_cast<double>(t2-t1)/CLOCKS_PER_SEC;
        cout << "Tiempo de ejecución\t= " << secs1 << " segundos." << endl;
    }

    if(PD){
        cout << "\n=============================================" << endl;
        cout << "|| ALGORITMO DE PROGRAMACIÓN DINÁMICA (PD) ||" << endl;
        cout << "=============================================" << endl;
        clock_t t3 = clock();
        cout << "Formas posibles\t\t= " << formasPD(n, k, potencias, rotos) << endl;
        clock_t t4 = clock();
        double secs2 = static_cast<double>(t4-t3)/CLOCKS_PER_SEC;
        cout << "Tiempo de ejecución\t= " << secs2 << " segundos." << endl;
    }

    cout << "\n==========================================" << endl;
    cout << "|| FORMA MÁS CORTA DE SUBIR LA ESCALERA ||" << endl;
    cout << "==========================================" << endl;

    vector<int> formaCorta = formaMasCortaPD(n,k,potencias,rotos);
    if(formaCorta.empty()){
        cout << "No existe camino posible!" << endl;
    }
    else{
        cout << "Largo del camino\t= " << formaCorta.size() - 1 << endl;
        cout << "Camino a seguir\t\t= ";
        for(int i = 1; i<formaCorta.size(); i++){
            cout << formaCorta[i] << " " ;
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}


/*  Algoritmo de Fuerza Bruta que calcula la cantidad de formas posibles de subir la escalera de 
    tamaño n, con pasos posibles de tamaño B[i], 0 <= i < k, k = B.size(), evitando pisar los escalones
    rotos, el vector rotos contiene los indices de los escalones dañados.  
    
    Esta función no la hicimos de tipo long long (como el de PD) ya que para valores de n muy grande
    este algoritmo no termina a ejecutarse debido a que su tiempo de ejecución es EXPONENCIAL    */
int formasFB(int n, int k, vector<int>& B, vector<int>& rotos) {
    if (n == 0) {
        return 1;
    }
    int total = 0;
    for (int i = 0; i < k; i++) {
        if (n - B[i] >= 0 && find(rotos.begin(), rotos.end(), n) == rotos.end()) {
            total += formasFB(n - B[i], k, B, rotos);
        }
    }
    return total;
}


/*  Algoritmo basado en Programación Dinámica que calcula la cantidad de formas posibles de subir la escalera de tamaño n,
    con pasos posibles de tamaño B[i], 0 <= i < k, k = B.size(),
    evitando pisar los escalones rotos, el vector rotos contiene los indices de los escalones dañados.
    
    Es de tipo long long ya que cuando n es muy grande (tambien depende el valor de r), la cantidad de formas 
    posibles para subir la escalera se vuelve extremadamente grande, ocasionando OverFlow.
    Aún siendo de tipo long long se genera OverFlow en ciertos casos.   */

unsigned long long int formasPD(int n, int k, vector<int>& B, vector<int>& rotos) {
    vector<unsigned long long int> aux(n + 1, 0);
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


/*  Algoritmo similar a la función FormasPD(), pero con leves modificaciones.
    Este algoritmo basado en PD retorna un vector con el camino mas corto posible para subir la escalera
    Recordemos que esta implementacion no se considera en nuestro analisis.*/
vector<int> formaMasCortaPD(int n, int k, vector<int>& B, vector<int>& rotos) {
    vector<long long> aux(n + 1, 0);
    vector<vector<int>> caminos(n + 1);
    aux[0] = 1;
    caminos[0] = {0}; // El camino para el escalón 0 es vacío
    for (int i = 1; i <= n; i++) {
        aux[i] = LLONG_MAX; // Inicializar el número de formas para el escalón i con un valor grande
        for (int j = 0; j < k; j++) {
            if (i - B[j] >= 0 && find(rotos.begin(), rotos.end(), i) == rotos.end()) {
                if (aux[i - B[j]] != LLONG_MAX && aux[i - B[j]] + 1 < aux[i]) {
                    aux[i] = aux[i - B[j]] + 1;
                    caminos[i] = caminos[i - B[j]];
                    caminos[i].push_back(i);
                }
            }
        }
    }
    return caminos[n];
}


/*  Función que retorna un vector con todas las potencias de p menores o iguales a n
    Por ejemplo, si p=2 y n=10 --> se genera un vector {1,2,4,8}    */
vector<int> creaPotencias(int p, int n) {
    vector<int> potencias;
    int pot = 1;
    while (pot <= n) {
        potencias.push_back(pot);
        pot *= p;
    }
    return potencias;
}

/*  Función que genera r escalones rotos aleatoriamente entre 1 y (n-1)
    El escalón n no puede estar roto, ya que no existiría solución.  
    Ademas el escalon 0 es considerado como el suelo, desde ahi se comienza a subir     */
void generaRotos(int r, int n, vector<int>& rotos){
    set<int> numeros;
    while (numeros.size() < r){
        numeros.insert(1 + rand() % (n-1));
    }
    rotos.assign(numeros.begin(), numeros.end());
}

/*  Funcón destinada a imprimir un vector que se necesite en su momento  */
void imprimeVector(vector<int> v){
    if (!v.empty()){
        for (int i = 0; i<v.size(); i++){
            cout << v[i] << " ";
        }
        cout << endl;
    }
    else{
        cout << "Se trató de imprimir un vector vacío!" << endl;
    }
}
