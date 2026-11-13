/*
 * Listado 1 - Problema G: "Compound Words"
 *
 * Que pide: dada una lista de 1 a 100 palabras (hasta fin de archivo), imprimir
 * en orden de diccionario todas las palabras compuestas UNICAS que se forman
 * concatenando dos palabras DIFERENTES (posiciones distintas) de la lista.
 *
 * Aproximacion: fuerza bruta sobre todos los pares ordenados (i, j) con i != j,
 * guardando cada concatenacion en un std::set<string>.
 *   - El set elimina duplicados (misma palabra formada de varias maneras).
 *   - El set mantiene sus elementos ordenados, asi que al recorrerlo ya salen en
 *     orden lexicografico.
 *
 * Flujo:
 *   1. Leer palabras hasta EOF y guardarlas en un vector.
 *   2. Doble bucle sobre pares (i, j), i != j; insertar inputs[i] + inputs[j].
 *   3. Imprimir el set completo, una palabra por linea.
 *
 * Complejidad: O(n^2 log(n^2)) con n <= 100 y palabras de <= 10 letras, es decir
 * a lo sumo 9900 inserciones de cadenas de <= 20 caracteres: trivial.
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set> // ?

using namespace std;

int main() {
    string xinput;
    // Resultado: compuestas unicas y ya ordenadas (set de strings usa orden lexicografico).
    set<string> outputs;
    // Palabras de entrada, en el orden en que llegan.
    vector<string> inputs;

    // Lectura hasta fin de archivo: "cin >> string" falla al llegar al EOF y corta
    // el bucle. Sirve tambien cuando hay varias palabras por linea o lineas vacias,
    // porque >> salta cualquier espacio en blanco.
    while (cin >> xinput){
        inputs.push_back(xinput);
    }

    // Se prueban todos los pares ordenados. El orden importa: "ab"+"cd" = "abcd"
    // es distinto de "cd"+"ab" = "cdab", por eso se recorren i y j completos y no j > i.
    for (int i = 0; i < inputs.size(); i++){
        for(int j = 0; j < inputs.size(); j++){
            // "dos palabras diferentes" se entiende como dos posiciones distintas:
            // una palabra no se concatena consigo misma.
            // OJO: si la lista trae la misma palabra repetida en dos posiciones
            // (p. ej. "a a"), el par (0,1) SI se acepta y produce "aa". Es la
            // lectura habitual del enunciado (posiciones distintas).
            if (i != j){
                outputs.insert(inputs[i]+inputs[j]);
            }
        }
    }

    // El set ya esta ordenado y sin repetidos: se imprime tal cual.
    for (string output : outputs){
        cout << output << endl;
    }

    return 0;
}
