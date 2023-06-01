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
