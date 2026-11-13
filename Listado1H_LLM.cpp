/*
 * Listado 1 - Problema H: "Srednji"
 *
 * Que pide: A es una permutacion de 1..N. Contar cuantos tramos contiguos
 * A[i..k] de longitud IMPAR tienen mediana igual a B.
 *
 * Idea clave: la mediana de un tramo de longitud impar es B si y solo si
 *   (a) el tramo contiene a B, y
 *   (b) hay tantos elementos menores que B como mayores que B.
 * Por eso se transforma cada elemento en -1 (< B), 0 (== B) o +1 (> B): un tramo
 * que contiene a B tiene mediana B exactamente cuando la suma transformada es 0.
 * (La longitud impar sale sola: #menores = #mayores y 1 elemento B => longitud 2m+1.)
 * Como A es permutacion, B aparece UNA sola vez.
 *
 * Con sumas de prefijos, suma[i..k] = prefijo[k+1] - prefijo[i]; se busca
 * prefijo[i] == prefijo[k+1] con i <= j <= k, donde j es la posicion de B.
 *
 * Flujo:
 *   1. Leer N, B y la secuencia.
 *   2. Transformar a -1/0/+1.
 *   3. Construir prefijo[0..N].
 *   4. Para la posicion j de B: contar con mapas de frecuencias los prefijos del
 *      lado izquierdo (indices 0..j) y del derecho (j+1..N), y sumar, para cada valor
 *      comun, frecIzq * frecDer.
 *
 * Complejidad: como B aparece una vez, el cuerpo del bucle sobre j se ejecuta una
 * sola vez, asi que el total es O(N log N) (por los std::map). Seria cuadratico
 * si hubiera muchos elementos == B, pero la entrada lo impide.
 * El resultado puede ser grande (hasta ~N^2/4), por eso se acumula en long long.
 */
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    // n: largo de la secuencia; b: mediana objetivo.
    int n, b;
    cin >> n >> b;

    // Lectura de la permutacion A.
    vector<int> secuencia(n);
    for (int i = 0; i < n; i++) {
        cin >> secuencia[i];
    }

    // Transformar: -1 si < b, 0 si == b, +1 si > b
    // TRUCO: se reemplazan los valores por su "signo" respecto de B; asi la
    // condicion "mediana == B" pasa a ser "suma == 0" en un tramo que contiene a B.
    vector<int> transformado(n);
    for (int i = 0; i < n; i++) {
        if (secuencia[i] < b) transformado[i] = -1;
        else if (secuencia[i] == b) transformado[i] = 0;
        else transformado[i] = 1;
    }

    // Calcular prefijos: prefijo[i] = suma de transformado[0..i-1]
    // Se usa tamano n+1 con prefijo[0] = 0 para poder expresar tramos que
    // empiezan en el indice 0.
    vector<int> prefijo(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefijo[i + 1] = prefijo[i] + transformado[i];
    }

    // Acumulador de la respuesta; long long porque puede superar el rango de int.
    long long contar = 0;

    // Para cada posición j donde hay un elemento == b
    // (al ser A una permutacion, el cuerpo de este bucle corre una sola vez)
    for (int j = 0; j < n; j++) {
        if (transformado[j] != 0) continue;

        // Contar subsecuencias [i, k] con i <= j <= k y suma transformada = 0
        // Suma en [i, k] = prefijo[k+1] - prefijo[i]
        // Queremos prefijo[k+1] == prefijo[i]

        // Frecuencia de prefijos en [0, j]
        // Estos son los posibles inicios i (el tramo debe empezar a la izquierda
        // de B o en B: i <= j, es decir, el prefijo usado es prefijo[i], i en 0..j).
        map<int, long long> frecIzq;
        for (int i = 0; i <= j; i++) {
            frecIzq[prefijo[i]]++;
        }

        // Frecuencia de prefijos en [j+1, n]
        // Estos son los posibles finales: k >= j <=> k+1 en j+1..n.
        map<int, long long> frecDer;
        for (int k = j + 1; k <= n; k++) {
            frecDer[prefijo[k]]++;
        }

        // Contar pares donde prefijo[i] == prefijo[k+1]
        // Cada valor comun aporta frecIzq * frecDer tramos (combinaciones inicio-fin).
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
