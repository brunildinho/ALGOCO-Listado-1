/*
 * Problema C: Sim
 *
 * Resumen: se simula un editor de texto con teclas especiales: '<' (Backspace,
 * borra el caracter anterior al cursor; si el cursor esta al inicio no hace nada),
 * '[' (Home: cursor al inicio de la linea), ']' (End: cursor al final) y cualquier
 * otro caracter se inserta en la posicion del cursor. Por cada caso (T <= 10, cada
 * linea de hasta 10^6 caracteres) se imprime el texto final.
 *
 * Aproximacion: en vez de mover un cursor por el medio del texto (costoso en una
 * cadena), se usa que el cursor solo puede estar en dos sitios "utiles": al final
 * o al inicio. Se mantienen dos estructuras:
 *   - caracteres (list<char>): texto ya "consolidado", al que se pueden agregar
 *     caracteres por el final (push_back) o por el inicio (push_front) en O(1).
 *   - frontline (vector<char>): lo escrito desde la ultima vez que se pulso Home,
 *     en orden de tecleo; queda pendiente de anteponer al texto consolidado.
 * La bandera endline indica el modo actual: true = cursor al final (se escribe
 * directamente en caracteres), false = cursor al inicio (se escribe en frontline).
 *
 * Flujo por caso:
 *   1. Leer la linea completa (getline, porque puede tener espacios).
 *   2. Recorrer cada caracter:
 *        '[' o ']' : volcar frontline al frente de caracteres (anteponiendo desde
 *                    el ultimo hasta el primero para conservar el orden), vaciarlo
 *                    y fijar el modo (false para '[', true para ']').
 *        '<'       : modo final -> pop_back de caracteres (si no esta vacio);
 *                    modo inicio -> pop_back de frontline (si no esta vacio).
 *        otro      : modo final -> push_back en caracteres; si no, push_back en frontline.
 *   3. Al terminar, volcar lo que quede pendiente en frontline y imprimir caracteres.
 *
 * Complejidad: cada caracter se inserta y se mueve/borra un numero constante de
 * veces, asi que O(L) por caso en tiempo y espacio, con L = longitud de la linea.
 */
#include <iostream>
#include <list>
#include <string>
#include <limits> // OJO: no se usa en este archivo (solo es un include sobrante)
#include <vector>

using namespace std;

int main(){
    int t; //Usar lista doble enlazada? (list<char> es justamente una lista doblemente enlazada)
    cin >> t;
    // TRUCO: cin >> t deja el '\n' en el buffer; sin este get() el primer getline
    // leeria una linea vacia en lugar del primer caso de prueba.
    cin.get();

    for (int i = 0; i < t; i++){
        string linea;
        getline(cin, linea); // getline porque la linea puede contener espacios
        // true: el cursor esta al final de la linea; false: esta al inicio (tras Home).
        bool endline = true;
        
        list<char> caracteres;   // texto consolidado
        vector<char> frontline;  // texto escrito tras un Home, aun sin anteponer
        for (char x : linea){
            if (x == '[') {
                // Home: lo pendiente en frontline pasa al frente del texto. Se recorre
                // al reves con push_front para que quede en el mismo orden en que se tecleo.
                if (!frontline.empty()){
                    for (int j = frontline.size() - 1; j >= 0; j--){
                        caracteres.push_front(frontline[j]);
                    }
                }
                frontline.clear();
                // A partir de aqui lo nuevo se escribe antes de todo lo anterior.
                endline = false;
            }
            else if (x == ']') {
                // End: igual volcado de lo pendiente y el cursor vuelve al final.
                if (!frontline.empty()){
                    for (int j = frontline.size() - 1; j >= 0; j--){
                        caracteres.push_front(frontline[j]);
                    }
                }
                frontline.clear();
                endline = true;
            }
            else if (x == '<') {
                // Backspace. Con el cursor al final borra el ultimo de caracteres; con
                // el cursor al inicio solo puede borrar lo tecleado tras el Home
                // (frontline); si esta vacio, el cursor esta al principio y no hace nada.
                if (endline && !caracteres.empty()) caracteres.pop_back();
                else if (!endline && !frontline.empty()) frontline.pop_back();
            }
            else {
                // Caracter normal: se inserta segun el modo.
                if (endline) caracteres.push_back(x);
                else {
                    frontline.push_back(x);
                }
            }
        }
        
        // Si la linea termino con el cursor en modo "inicio", falta anteponer lo pendiente.
        if (!frontline.empty()) {
            for (int j = frontline.size() - 1; j >= 0; j--){
                caracteres.push_front(frontline[j]);
            }
        }

        // Salida: el texto final del caso, en una linea.
        for (char x : caracteres){
            cout << x;
        }
        cout << endl;
    }
    return 0;
}
