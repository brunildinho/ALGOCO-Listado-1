/*
 * Problema B: Bungee Builder
 *
 * Resumen: hay N montanas con alturas H_i. Se construye un puente horizontal entre
 * dos montanas distintas, a una altura <= min de ambas y estrictamente mayor que
 * todas las montanas intermedias. La atraccion se abre en algun punto del puente y
 * el salto es la distancia vertical hasta el suelo que hay debajo. Se pide la
 * maxima distancia de salto posible (0 si no se puede construir ningun puente).
 * Limites: N <= 10^6, H_i <= 10^9 (tiempo 1 s) => hace falta O(N).
 *
 * Aproximacion (lo que hace el codigo): recorrido lineal con "maximo corriente" y
 * "minimo desde ese maximo". En cada pasada, max1 es la altura del ultimo "pico"
 * (maximo de prefijo, con >=) y min el valor mas bajo visto desde ese pico. Cuando
 * aparece una montana x >= max1 se cierra un puente a altura max1 sobre ese tramo y
 * el hueco mas profundo bajo el puente es max1 - min. Ese tramo entre dos picos
 * consecutivos es el candidato; se guarda el mejor en max2.
 * Como el recorrido izquierda->derecha solo cierra tramos cuando aparece un pico
 * igual o mayor, el tramo final (despues del ultimo maximo, que acaba "cuesta
 * abajo") no se evalua; por eso se repite el mismo procedimiento de derecha a
 * izquierda, donde esos tramos si quedan acotados por un pico.
 *
 * Flujo:
 *   1. Leer N y las alturas, guardandolas en un vector, y hacer la pasada izq->der.
 *   2. Reiniciar max1 y min, y hacer la pasada der->izq sobre el vector.
 *   3. Imprimir max2.
 *
 * Complejidad: O(N) en tiempo y O(N) en espacio (el vector, necesario para la
 * segunda pasada).
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // max1: altura del ultimo pico (maximo de prefijo); min: minimo desde ese pico;
    // max2: mejor distancia de salto encontrada hasta ahora (la respuesta).
    // Se inicializan en 0, lo cual es valido porque H_i >= 0.
    int n, min = 0, max1 = 0, max2 = 0;
    vector<int> picos; // todas las alturas (se necesitan para la pasada inversa)
    cin >> n;
    // Pasada izquierda -> derecha, leyendo y procesando a la vez.
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        picos.push_back(x);
        if (x >= max1){
            // TRUCO: se usa >= (no >) para que un pico igual tambien cierre el tramo
            // y reinicie el minimo; el puente puede apoyarse en dos montanas iguales.
            // Se cierra el tramo: puente a altura max1, mayor caida = max1 - min.
            // (Si x es adyacente al pico, min == max1 y el candidato es 0.)
            if ((max1-min) > max2) max2 = (max1-min);
            // x pasa a ser el nuevo pico y el minimo del nuevo tramo.
            max1 = x;
            min = x;
        }
        else{
            // Montana dentro del tramo: solo se actualiza el punto mas bajo.
            if (x < min) min = x;
        }
    }
    // Segunda pasada, ahora de derecha a izquierda, con el estado reiniciado.
    // OJO: el reinicio de min y max1 a 0 es correcto porque H_i >= 0.
    min = 0; max1 = 0;
    for (int i = picos.size() - 1; i >= 0; i--){
        if (picos[i] >= max1){
            if ((max1-min) > max2) max2 = (max1-min);
            max1 = picos[i];
            min = picos[i];
        }
        else{
            if (picos[i] < min) min = picos[i];
        }
    }

    cout << max2;
    return 0;

}
