/*
 * Listado 1 - Problema F: "Saving Princess Peach"
 *
 * Que pide: hay N obstaculos numerados 0..N-1. Mario dice haber encontrado Y
 * obstaculos (con repetidos y en desorden). Hay que imprimir, en orden
 * creciente, los obstaculos que NO menciono, y al final la linea
 * "Mario got X of the dangerous obstacles." con X = obstaculos distintos mencionados.
 *
 * Aproximacion: un std::set<int> hace de "conjunto de obstaculos vistos".
 *   - El set descarta duplicados solo, asi que su tamano final es exactamente X.
 *   - Luego se recorre 0..N-1 en orden; como el recorrido ya es creciente, no
 *     hace falta ordenar la salida: basta imprimir los i que no estan en el set.
 *
 * Flujo:
 *   1. Leer N e Y.
 *   2. Insertar los Y valores en el set (los repetidos no cambian nada).
 *   3. Imprimir cada i en [0, N) que no este en el set.
 *   4. Imprimir el resumen con obstaculos.size().
 *
 * Complejidad: O(Y log Y + N log Y) tiempo, O(Y) memoria. Con N <= 100 e Y <= 200
 * es inmediato.
 */
#include <iostream>
#include <set>

using namespace std;

int main(){
    // n: total de obstaculos; y: cuantos dijo haber visto Mario (con repeticiones).
    int n, y;
    // Conjunto de obstaculos distintos que Mario si encontro. Insertar un
    // elemento ya presente no hace nada, lo que elimina los "contados mas de una vez".
    set<int> obstaculos;
    cin >> n;
    cin >> y;
    // Lectura de las Y declaraciones de Mario, en el orden desordenado en que vienen.
    for (int i = 0; i < y; i++){
        int x;
        cin >> x;
        obstaculos.insert(x);
    }

    // Se recorre el rango completo 0..n-1 en orden creciente: todo i ausente del
    // set es un obstaculo que Mario paso por alto. count() devuelve 0 o 1 en un set.
    // TRUCO: el orden creciente de la salida sale gratis del propio recorrido;
    // no se necesita ordenar nada.
    for (int i = 0; i < n; i++){
        if (obstaculos.count(i) == 0){
            cout << i << endl;
        }
    }
    // Linea final exigida por el enunciado. size() del set = cantidad de obstaculos
    // DISTINTOS encontrados (no Y, que puede incluir repetidos).
    cout << "Mario got "<< obstaculos.size() <<" of the dangerous obstacles." << endl;

}
