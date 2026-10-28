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
    
    vector<int> transformado(n);
    for (int i = 0; i < n; i++) {
        if (secuencia[i] < b) transformado[i] = -1;
        else if (secuencia[i] == b) transformado[i] = 0;
        else transformado[i] = 1;
    }

    vector<int> prefijo(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefijo[i + 1] = prefijo[i] + transformado[i];
    }
    
    long long contar = 0;
    

    for (int j = 0; j < n; j++) {
        if (transformado[j] != 0) continue;
        
        map<int, long long> frecIzq;
        for (int i = 0; i <= j; i++) {
            frecIzq[prefijo[i]]++;
        }
        
        map<int, long long> frecDer;
        for (int k = j + 1; k <= n; k++) {
            frecDer[prefijo[k]]++;
        }
        
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
