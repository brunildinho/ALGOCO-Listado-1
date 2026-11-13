/*
 * Problema E: Stock Prices (variante 2, "LLM": matching separado para sell y buy)
 *
 * Resumen: se reciben ordenes "buy/sell x shares at y". Si bid >= ask se hace una
 * transaccion al precio del vendedor hasta agotar una de las dos ordenes. Tras CADA
 * orden se imprime "ask bid stock": menor precio de venta pendiente, mayor precio
 * de compra pendiente y precio de la ultima transaccion ("-" si no esta definido).
 * Hasta 100 casos, n <= 1000 ordenes, x e y <= 1000.
 *
 * Aproximacion: dos map<precio, cantidad> (lista_ventas, lista_compras) ordenados
 * por precio; ask = lista_ventas.begin(), bid = lista_compras.rbegin().
 *
 * DIFERENCIA con las otras variantes: respecto de Listado1E.cpp, lee "shares"/"at"
 * como strings, imprime en el orden correcto (ask bid stock) con salto de linea y
 * reinicia ask/bid en cada orden. Respecto de E_LLM2, aqui el matching se hace con
 * bucles mas elaborados (en sell, recorre desde el nivel recien insertado hacia
 * arriba y las compras de mayor a menor; en buy, recorre todas las compras de menor
 * a mayor), y usa const_cast y borrado en un paso aparte; E_LLM2 es una version
 * mas simple y compacta con un unico bloque de limpieza.
 *
 * Flujo por orden:
 *   1. Leer tipo, cantidad, las palabras "shares" y "at" (descartadas) y precio.
 *   2. sell: sumar al nivel de precio y cruzar con las compras de mayor precio
 *      (rbegin hacia abajo) que cumplan precio_compra >= precio_venta.
 *      buy: sumar al nivel y cruzar con las ventas de menor precio hasta
 *      upper_bound(precio_compra).
 *   3. Recalcular ask/bid desde begin()/rbegin() (o -1 si el mapa esta vacio).
 *   4. Imprimir "ask bid stock" sustituyendo por '-' los no definidos (<= 0).
 *
 * Complejidad: por orden se recorren como mucho los niveles de precio distintos
 * (<= 1000), asi que O(n * P) por caso en tiempo; espacio O(P).
 * Verificado contra el ejemplo del enunciado.
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        int n; cin >> n;
        // precio -> cantidad pendiente en ese nivel, ordenado por precio.
        map<int, int> lista_ventas, lista_compras;
        // -1 = indefinido (se imprime '-'). precio_stock persiste entre ordenes
        // del mismo caso (es el precio de la ultima transaccion hasta el momento).
        int precio_compra_output = -1, precio_venta_output = -1, precio_stock = -1;
        // aks price: precio menor de venta || bid price: precio mayor de compra || stock price: precio ultima transaccion
        for (int j = 0; j < n; j++){

            // Lectura de "tipo x shares at y": las palabras fijas se leen y se descartan.
            string tipo_orden, shares_word, at_word;
            int nro_acciones, precio_acciones;
            cin >> tipo_orden >> nro_acciones >> shares_word >> at_word >> precio_acciones;

            if (tipo_orden == "sell"){
                // Se acumula la orden en su nivel de precio.
                lista_ventas[precio_acciones] += nro_acciones;
                
                // Se parte del nivel recien insertado hacia precios mayores. En la practica solo
                // el nivel nuevo puede cruzar (los demas ya estaban sin cruce antes de esta orden).
                for (auto it_venta_iter = lista_ventas.find(precio_acciones); it_venta_iter != lista_ventas.end(); ){
                    int precio_venta = it_venta_iter->first;
                    int& cantidad_venta = it_venta_iter->second;
                    
                    // TRUCO: rbegin() recorre las compras de mayor a menor precio, que es la
                    // prioridad correcta: el vendedor se cruza primero con el mejor bid.
                    auto it_compra = lista_compras.rbegin();
                    while (it_compra != lista_compras.rend() && cantidad_venta > 0) {
                        if (it_compra->first >= precio_venta) {
                            // OJO: el const_cast es innecesario; el valor (second) de un map<int,int>
                            // no es const (solo lo es la clave). No cambia el comportamiento.
                            int& cantidad_compra = const_cast<int&>(it_compra->second);
                            int transaccion = min(cantidad_compra, cantidad_venta);
                            if (transaccion > 0) {
                                // Transaccion al precio del vendedor.
                                precio_stock = precio_venta;
                                cantidad_compra -= transaccion;
                                cantidad_venta -= transaccion;
                            }
                        }
                        ++it_compra;
                    }
                    
                    // Se borra el nivel de venta si se agoto (erase devuelve el siguiente).
                    if (it_venta_iter->second == 0) {
                        it_venta_iter = lista_ventas.erase(it_venta_iter);
                    } else {
                        ++it_venta_iter;
                    }
                }
                
                // Las compras que quedaron en cero no se borraron dentro del bucle
                // (para no invalidar el reverse_iterator); se limpian aqui.
                for (auto it = lista_compras.begin(); it != lista_compras.end(); ) {
                    if (it->second == 0) {
                        it = lista_compras.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
            else if (tipo_orden == "buy"){
                lista_compras[precio_acciones] += nro_acciones;
                
                // Se recorren las compras de menor a mayor; solo la recien insertada puede
                // cruzar realmente, las demas no tienen ventas con precio <= el suyo.
                for (auto it_compra = lista_compras.begin(); it_compra != lista_compras.end(); ){
                    int precio_compra = it_compra->first;
                    int& cantidad_compra = it_compra->second;

                    // Ventas con precio <= precio_compra, de menor a mayor (mejor ask primero).
                    // upper_bound se reevalua en cada iteracion y sigue siendo valido tras erase.
                    for (auto it = lista_ventas.begin(); it != lista_ventas.upper_bound(precio_compra); ){
                        int precio_venta = it->first;
                        int& cantidad_venta = it->second;
                        int transaccion = min(cantidad_compra, cantidad_venta);
                        if (transaccion > 0){
                            precio_stock = precio_venta;
                            cantidad_compra -= transaccion;
                            cantidad_venta -= transaccion;
                        }
                        
                        if (it->second == 0) {
                            it = lista_ventas.erase(it);
                        } else {
                            ++it;
                        }
                    }
                    
                    if (it_compra->second == 0) {
                        it_compra = lista_compras.erase(it_compra);
                    } else {
                        ++it_compra;
                    }
                }
            }
            
            // Se reinician en cada orden para que un mapa vacio produzca '-' y no un valor viejo.
            precio_venta_output = -1;
            precio_compra_output = -1;
            
            if (!lista_ventas.empty()) {
                precio_venta_output = lista_ventas.begin()->first; // ask: menor precio de venta
            }
            if (!lista_compras.empty()) {
                precio_compra_output = lista_compras.rbegin()->first; // bid: mayor precio de compra
            }
            // Salida "ask bid stock"; los precios son >= 1, asi que <= 0 equivale a indefinido.
            // Se imprime por partes (no con ?:) para no mezclar char e int en un mismo ternario.
            if (precio_venta_output <= 0) cout << '-';
            else cout << precio_venta_output;
            cout << ' ';
            
            if (precio_compra_output <= 0) cout << '-';
            else cout << precio_compra_output;
            cout << ' ';
            
            if (precio_stock <= 0) cout << '-';
            else cout << precio_stock;
            cout << endl;
        }
    }




    return 0;
}
