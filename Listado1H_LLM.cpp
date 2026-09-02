#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    int n, b;
    cin >> n >> b;
    
    vector<int> secuencia(n);
    for (int i = 0; i < n; i++) {
        cin >> secuencia[i];
    }
    
    // Transformar: -1 si < b, 0 si == b, +1 si > b
    vector<int> transformado(n);
    for (int i = 0; i < n; i++) {
        if (secuencia[i] < b) transformado[i] = -1;
        else if (secuencia[i] == b) transformado[i] = 0;
        else transformado[i] = 1;
    }
    
    // Calcular prefijos: prefijo[i] = suma de transformado[0..i-1]
    vector<int> prefijo(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefijo[i + 1] = prefijo[i] + transformado[i];
    }
    
    long long contar = 0;
    
    // Para cada posición j donde hay un elemento == b
    for (int j = 0; j < n; j++) {
        if (transformado[j] != 0) continue;
        
        // Contar subsecuencias [i, k] con i <= j <= k y suma transformada = 0
        // Suma en [i, k] = prefijo[k+1] - prefijo[i]
        // Queremos prefijo[k+1] == prefijo[i]
        
        // Frecuencia de prefijos en [0, j]
        map<int, long long> frecIzq;
        for (int i = 0; i <= j; i++) {
            frecIzq[prefijo[i]]++;
        }
        
        // Frecuencia de prefijos en [j+1, n]
        map<int, long long> frecDer;
        for (int k = j + 1; k <= n; k++) {
            frecDer[prefijo[k]]++;
        }
        
        // Contar pares donde prefijo[i] == prefijo[k+1]
        for (auto& par : frecIzq) {
            int valor = par.first;
            long long freqI = par.second;
            if (frecDer.count(valor)) {
                contar += freqI * frecDer[valor];
            }
        }
    }
    
    cout << contar << endl;
    
    return 0;
}
