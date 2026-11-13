/*
 * Problema D: Integer Lists
 *
 * Resumen: lenguaje con dos funciones sobre una lista de enteros: 'R' (invertir) y
 * 'D' (eliminar el primer elemento; error si la lista esta vacia). Un programa es
 * una cadena de R y D (hasta 10^5 caracteres) que se aplica de izquierda a derecha
 * a una lista de hasta 10^5 elementos, dada como "[x1,x2,...,xn]". Hasta 100 casos.
 * Se imprime la lista resultante o "error".
 *
 * Aproximacion: invertir la lista de verdad en cada 'R' costaria O(n) por operacion
 * (O(|p|*n) en total, demasiado). En su lugar se mantiene un deque y una bandera
 * "reversed" que indica si la lista esta conceptualmente invertida:
 *   - 'R' : solo se alterna la bandera, O(1).
 *   - 'D' : si no esta invertida, el "primer" elemento es el front del deque
 *           (pop_front); si lo esta, el "primer" elemento es el back (pop_back).
 * Al final, si esta invertida se imprime recorriendo desde el back.
 *
 * Flujo por caso:
 *   1. Leer el programa (comando), n (l, no se usa despues) y la lista como un unico
 *      token de texto (no tiene espacios).
 *   2. Parsear la lista a mano separando por comas y llenando el deque.
 *   3. Ejecutar el programa caracter a caracter; si 'D' sobre lista vacia -> "error".
 *   4. Si no hubo error, imprimir "[a,b,...]" en el orden segun la bandera.
 *
 * Complejidad: O(|p| + n) por caso en tiempo y espacio.
 */
#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main (){
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        int l;
        string input1, comando;
        // flag_error: se aplico 'D' sobre lista vacia; reversed: la lista esta invertida
        // de forma "virtual" (el deque guarda el orden original).
        bool flag_error = false, reversed = false;
        cin >> comando;
        cin >> l; // numero de elementos; no se usa (la lista se parsea hasta ']')
        cin >> input1; // la lista completa, sin espacios, ej. "[1,2,3]"

        /*
        cout << "\nL obtenido: " << l << endl;
        cout << "Comando obtenido: " << comando << endl;
        */

        // Parseo manual de la lista: x acumula los digitos del numero actual.
        string x;
        // OJO: se llama "pila" pero es un deque; se necesita acceso por ambos extremos.
        deque<int> pila;
        for (int j = 0; j < input1.length(); j++){
            if (input1[j] == '[') continue;
            else if (input1[j] == ']'){
                // Fin de la lista: guardar el ultimo numero (si lo hay; "[]" no tiene).
                if (!x.empty()){
                    pila.push_back(stoi(x));

                    //cout << pila.back() << endl;

                    x.clear();
                }
                break;
            }
            else if (input1[j] == ',' && x.length() != 0){
                // Coma: se cierra el numero actual.
                pila.push_back(stoi(x));

                //cout << pila.back() << endl;

                x.clear();
            }
            else {
                // Digito del numero actual.
                // OJO: una ',' con x vacio caeria aqui y se agregaria a x; no ocurre
                // con entradas validas (nunca hay comas consecutivas).
                x += input1[j];
            }
        }
        // Ejecucion del programa BAPC.
        for (int j = 0; j < comando.length(); j++){
            if (comando[j] == 'R'){
                // TRUCO: invertir en O(1) alternando una bandera en vez de mover datos.
                reversed = !reversed;
            }
            else if (comando[j] == 'D'){
                if (pila.empty()){
                    cout << "error" << endl;
                    flag_error = true;
                    break;
                }
                else {
                    //cout << "eliminando..." << pila.front() << endl;
                    // "Primer elemento" depende de la bandera: extremo opuesto si esta invertida.
                    if (!reversed) pila.pop_front();
                    else pila.pop_back();
                }
            }
        }

        // Ya se imprimio "error": pasar al siguiente caso sin imprimir lista.
        if (flag_error) continue;

        // Salida: se vacia el deque desde el extremo que corresponda segun la bandera;
        // la coma se imprime solo si quedan mas elementos.
        cout << '[';
        if (!reversed){
            while(!pila.empty()){
                cout << pila.front();
                pila.pop_front();
                if (!pila.empty()) cout << ',';
            }
        }
        else{
            while(!pila.empty()){
            cout << pila.back();
            pila.pop_back();
            if (!pila.empty()) cout << ',';
            }
        }

        cout << ']' << endl;

    }

    return 0;
}
