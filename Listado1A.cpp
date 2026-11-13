/*
 * Problema A: Game of Throwns
 *
 * Resumen: n ninos en circulo (0..n-1, sentido horario); el huevo empieza en el
 * nino 0. Hay k comandos: un entero t (lanzar t posiciones, negativo = antihorario,
 * con vuelta circular) o "undo m" (deshacer los ultimos m lanzamientos; un undo
 * nunca deshace otro undo). Se imprime el nino que tiene el huevo al final.
 *
 * Aproximacion: simulacion directa con una pila (TDA stack) que guarda los
 * desplazamientos de los lanzamientos vigentes. Deshacer un lanzamiento es
 * aplicar el desplazamiento contrario y sacarlo de la pila.
 *
 * Flujo:
 *   1. Leer n y k; la posicion actual p parte en 0.
 *   2. Por cada comando leer un token: si es "undo", leer m y repetir m veces
 *      (tope de la pila -> mover p en sentido contrario, pop).
 *      Si no, es un entero: mover p, y apilar el desplazamiento.
 *   3. Imprimir p.
 *
 * Complejidad: cada lanzamiento se apila una vez y se desapila a lo sumo una vez,
 * asi que O(k) en tiempo y O(k) en espacio (con k <= 100, n <= 30 sobra).
 */
#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main(){
    int n, k; // N: Nro estudiantes; K: nro de comandos llamados
    // Pila con los desplazamientos (sin reducir modulo n) de los lanzamientos vigentes.
    // Los "undo" no se apilan: solo consumen elementos de esta pila.
    stack<int> ordenes;
    cin >> n; //tamaño
    cin >> k; //ordenes
    int p = 0; // posicion actual del huevo (siempre normalizada en [0, n-1])


    for (int i = 0; i < k; i++){
        // TRUCO: se lee el comando como string porque puede ser un numero (posiblemente
        // negativo) o la palabra "undo"; despues se convierte con stoi cuando corresponde.
        string x;
        cin >> x;
        if (x == "undo"){
            // El siguiente token es la cantidad m de lanzamientos a deshacer.
            cin >> x;
            int undos;
            undos = stoi(x);
            for (int j = 0; j < undos; j++){
                // Deshacer = lanzar -top. TRUCO: en C++ el % con operando negativo da
                // resultado negativo o cero; por eso (-top % n) cae en (-n, n) y se le
                // suma n antes del % final para dejar p en [0, n-1].
                p = (p + (-ordenes.top() % n) + n) % n;
                ordenes.pop();
            }
        }
        else{
            int jumps = stoi(x);
            // TRUCO: doble modulo ((a % n) + n) % n para obtener el modulo matematico
            // (no negativo) cuando jumps es negativo (lanzamiento antihorario).
            p = ((p + jumps) % n + n) % n;
            ordenes.push(jumps);   
        }
    }
    cout << p << endl;
}
