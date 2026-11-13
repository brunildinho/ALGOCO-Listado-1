/*
 * Problema E: Stock Prices (variante 3, "LLM2": version simplificada)
 *
 * Resumen: se reciben ordenes "buy/sell x shares at y". Si bid >= ask se hace una
 * transaccion al precio del vendedor hasta agotar una de las dos ordenes. Tras CADA
 * orden se imprime "ask bid stock" (menor precio de venta pendiente, mayor precio
 * de compra pendiente, precio de la ultima transaccion; "-" si no esta definido).
 * Hasta 100 casos, n <= 1000 ordenes, x e y <= 1000.
 *
 * Aproximacion: dos map<precio, cantidad> (lista_ventas, lista_compras) ordenados.
 * ask = lista_ventas.begin(), bid = lista_compras.rbegin().
 *
 * DIFERENCIA con las otras variantes: es la mas simple y compacta. Solo se cruza
 * la orden recien llegada contra el lado contrario (un unico bucle por tipo de
 * orden, sin bucles anidados sobre todo el mapa como en E y E_LLM), y la limpieza
 * de niveles en cero se hace al final de cada orden para ambos mapas. La salida se
 * arma con to_string y '\n' en vez de endl.
 *
 * Flujo por orden:
 *   1. Leer tipo, cantidad, "shares", "at" (se descartan) y precio.
 *   2. sell: acumular en su nivel y cruzar con las compras de mayor a menor precio
 *      mientras precio_compra >= precio_venta y quede cantidad por vender.
 *      buy: acumular en su nivel y cruzar con las ventas de menor a mayor precio
 *      mientras precio_venta <= precio_compra y quede cantidad por comprar.
 *   3. Borrar los niveles que quedaron en cero en ambos mapas.
 *   4. Calcular ask/bid y imprimir "ask bid stock".
 *
 * Complejidad: por orden O(P) niveles recorridos como mucho (P <= 1000), asi que
 * O(n * P) por caso (con el factor log del map en los accesos por clave).
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
        // -1 = indefinido (se imprime '-'). precio_stock persiste entre ordenes del caso.
        int precio_compra_output = -1, precio_venta_output = -1, precio_stock = -1;
        // aks price: precio menor de venta || bid price: precio mayor de compra || stock price: precio ultima transaccion
        for (int j = 0; j < n; j++){

            // "tipo x shares at y": las palabras fijas se leen y se descartan.
            string tipo_orden, shares_word, at_word;
            int nro_acciones, precio_acciones;
            cin >> tipo_orden >> nro_acciones >> shares_word >> at_word >> precio_acciones;

            if (tipo_orden == "sell"){
                lista_ventas[precio_acciones] += nro_acciones;
                
                // Matching: buscar todas las compras con precio >= precio_venta
                // TRUCO: rbegin() da las compras de mayor a menor precio (mejor bid primero).
                // Se usa lista_ventas[precio_acciones] como contador de lo que falta vender
                // (el nivel existe, recien se creo/acumulo arriba).
                auto it_compra = lista_compras.rbegin();
                while (it_compra != lista_compras.rend() && lista_ventas[precio_acciones] > 0) {
                    if (it_compra->first >= precio_acciones) {
                        int transaccion = min(it_compra->second, lista_ventas[precio_acciones]);
                        it_compra->second -= transaccion;
                        lista_ventas[precio_acciones] -= transaccion;
                        // Transaccion al precio del vendedor (la orden que acaba de llegar).
                        precio_stock = precio_acciones;
                    }
                    ++it_compra;
                }
            }
            else if (tipo_orden == "buy"){
                lista_compras[precio_acciones] += nro_acciones;
                
                // Matching: buscar todas las ventas con precio <= precio_compra
                // Se recorren las ventas de menor a mayor precio (mejor ask primero).
                for (auto it = lista_ventas.begin(); it != lista_ventas.end() && lista_compras[precio_acciones] > 0; ){
                    if (it->first <= precio_acciones) {
                        int transaccion = min(it->second, lista_compras[precio_acciones]);
                        it->second -= transaccion;
                        lista_compras[precio_acciones] -= transaccion;
                        // Transaccion al precio del vendedor (la venta que estaba en el libro).
                        precio_stock = it->first;
                    }
                    
                    // Se borra el nivel de venta si se agoto (erase devuelve el siguiente iterador).
                    if (it->second == 0) {
                        it = lista_ventas.erase(it);
                    } else {
                        ++it;
                    }
                }
            }

            // Limpiar órdenes completadas
            // (los niveles en cero deben desaparecer para que begin()/rbegin() den ask/bid reales)
            for (auto it = lista_compras.begin(); it != lista_compras.end(); ) {
                if (it->second == 0) {
                    it = lista_compras.erase(it);
                } else {
                    ++it;
                }
            }
            for (auto it = lista_ventas.begin(); it != lista_ventas.end(); ) {
                if (it->second == 0) {
                    it = lista_ventas.erase(it);
                } else {
                    ++it;
                }
            }

            // Output después de cada orden
            // ask: menor precio de venta; bid: mayor precio de compra; -1 si no hay.
            precio_venta_output = lista_ventas.empty() ? -1 : lista_ventas.begin()->first;
            precio_compra_output = lista_compras.empty() ? -1 : lista_compras.rbegin()->first;
            
            // TRUCO: se usa to_string en ambas ramas del ternario para que ambas sean
            // std::string (con "-" y un int mezclarian tipos). '\n' en lugar de endl evita
            // vaciar el buffer en cada linea.
            cout << (precio_venta_output <= 0 ? "-" : to_string(precio_venta_output)) << ' ' 
                 << (precio_compra_output <= 0 ? "-" : to_string(precio_compra_output)) << ' ' 
                 << (precio_stock <= 0 ? "-" : to_string(precio_stock)) << '\n';
        }
    }




    return 0;
}
