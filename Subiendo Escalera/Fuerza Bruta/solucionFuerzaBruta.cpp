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

/*
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
    for (int i = 0; i <= (log(n) / log(p)); i++) {
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
*/

/*
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void encontrarFormasPosibles(int pos, int n, int p, vector<int>& escalones_rotos, vector<int>& forma_actual, vector<vector<int>>& formas) {
    if (pos == n) {
        formas.push_back(forma_actual);
        return;
    }
    
    for (int i = 0; i <= (log(n) / log(p)); i++) {
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

int main() {
    int n = 10;  // Número de escalones
    int p = 2;   // Potencia de salto
    int r = 3;   // Número de escalones rotos
    
    vector<int> escalones_rotos = {4, 5, 8};  // Índices de los escalones rotos
    
    vector<vector<int>> formas;
    vector<int> forma_actual;
    
    encontrarFormasPosibles(0, n, p, escalones_rotos, forma_actual, formas);
    
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
*/


/*

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> encontrarFormasPosibles(int n, int p, int r, vector<int>& escalones_rotos) {
    vector<vector<int>> formas;
    
    vector<int> forma_inicial;
    forma_inicial.push_back(0);  // Comenzar en el escalón 0
    
    vector<vector<int>> formas_actuales;
    formas_actuales.push_back(forma_inicial);
    
    while (!formas_actuales.empty()) {
        vector<int> forma_actual = formas_actuales.back();
        formas_actuales.pop_back();
        
        int pos_actual = forma_actual.back();
        
        if (pos_actual == n) {
            formas.push_back(forma_actual);
            continue;
        }
        
        for (int i = 0; i <= (log(n) / log(p)); i++) {
            int siguiente_escalón = pos_actual + pow(p, i);
            
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
            
            vector<int> nueva_forma = forma_actual;
            nueva_forma.push_back(siguiente_escalón);
            formas_actuales.push_back(nueva_forma);
        }
    }
    
    return formas;
}

int main() {
    int n = 10;  // Número de escalones
    int p = 2;   // Potencia de salto
    int r = 3;   // Número de escalones rotos
    
    vector<int> escalones_rotos = {4, 5, 8};  // Índices de los escalones rotos
    
    vector<vector<int>> formas = encontrarFormasPosibles(n, p, r, escalones_rotos);
    
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


*/


// ESTA SOLUCION ESTA BIEN IGUAL, 
// PERO int pos_actual = forma_actual.empty() ? 0 : forma_actual.back();
// esa instruccion no me gusto, asi que le pedi a gpt otra propuesta.
/*
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> encontrarFormasPosibles(int n, int p, int r, vector<int>& escalones_rotos) {
    vector<vector<int>> formas;
    
    vector<int> forma_inicial;
    
    vector<vector<int>> formas_actuales;
    formas_actuales.push_back(forma_inicial);
    
    while (!formas_actuales.empty()) {
        vector<int> forma_actual = formas_actuales.back();
        formas_actuales.pop_back();
        
        int pos_actual = forma_actual.empty() ? 0 : forma_actual.back();
        
        if (pos_actual == n) {
            if (!forma_actual.empty() && forma_actual[0] == 0)
                forma_actual.erase(forma_actual.begin()); // Eliminar el 0 al comienzo
            formas.push_back(forma_actual);
            continue;
        }
        
        for (int i = 0; i <= (log(n) / log(p)); i++) {
            int siguiente_escalón = pos_actual + pow(p, i);
            
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
            
            vector<int> nueva_forma = forma_actual;
            nueva_forma.push_back(siguiente_escalón);
            formas_actuales.push_back(nueva_forma);
        }
    }
    
    return formas;
}

int main() {
    int n = 10;  // Número de escalones
    int p = 2;   // Potencia de salto
    int r = 3;   // Número de escalones rotos
    
    vector<int> escalones_rotos = {4, 5, 8};  // Índices de los escalones rotos
    
    vector<vector<int>> formas = encontrarFormasPosibles(n, p, r, escalones_rotos);
    
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

*/

// esta solucion me parece bien, ya que no tiene instrucciones extrañas, quizas hay otra forma de eliminar el 0 del comienzo, (linea 345)
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> encontrarFormasPosibles(int n, int p, int r, vector<int>& escalones_rotos) {
    vector<vector<int>> formas;
    
    vector<int> forma_inicial;
    
    vector<vector<int>> formas_actuales;
    formas_actuales.push_back(forma_inicial);
    
    while (!formas_actuales.empty()) {
        vector<int> forma_actual = formas_actuales.back();
        formas_actuales.pop_back();
        
        int pos_actual;
        if (forma_actual.empty()) {
            pos_actual = 0;
        } else {
            pos_actual = forma_actual.back();
        }
        
        if (pos_actual == n) {
            if (!forma_actual.empty() && forma_actual[0] == 0)
                forma_actual.erase(forma_actual.begin()); // Eliminar el 0 al comienzo
            formas.push_back(forma_actual);
            continue;
        }
        
        for (int i = 0; i <= (log(n) / log(p)); i++) {
            int siguiente_escalón = pos_actual + pow(p, i);
            
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
            
            vector<int> nueva_forma = forma_actual;
            nueva_forma.push_back(siguiente_escalón);
            formas_actuales.push_back(nueva_forma);
        }
    }
    
    return formas;
}

int main() {
    int n = 10;  // Número de escalones
    int p = 2;   // Potencia de salto
    int r = 3;   // Número de escalones rotos
    
    vector<int> escalones_rotos = {4, 5, 8};  // Índices de los escalones rotos
    
    vector<vector<int>> formas = encontrarFormasPosibles(n, p, r, escalones_rotos);
    
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

