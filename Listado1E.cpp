/*
 * Problema E: Stock Prices (variante 1, la original del autor)
 *
 * Resumen: se reciben ordenes "buy/sell x shares at y". Cuando el precio de compra
 * (bid) >= precio de venta (ask) se produce una transaccion al precio del vendedor,
 * hasta agotar una de las dos ordenes. Tras CADA orden hay que imprimir
 * "ask bid stock": ask = menor precio de venta pendiente, bid = mayor precio de
 * compra pendiente, stock = precio de la ultima transaccion ("-" si no esta definido).
 * Hasta 100 casos, n <= 1000 ordenes, x e y <= 1000.
 *
 * Aproximacion: dos map<precio, cantidad> ordenados (lista_ventas y lista_compras)
 * que agregan cantidades por nivel de precio. El menor precio de venta es
 * begin() y el mayor de compra es rbegin(). Tras insertar cada orden se recorren las
 * compras y, para cada una, las ventas con precio <= su precio (upper_bound),
 * cruzandolas y borrando los niveles que quedan en cero.
 *
 * DIFERENCIA con las otras variantes (E_LLM y E_LLM2): esta es la primera version
 * y el "matching" es generico (el mismo bloque para buy y sell, recorriendo las
 * compras de menor a mayor precio). La lectura usa cin.get() para saltar texto, y
 * la impresion es distinta. E_LLM y E_LLM2 leen las palabras "shares"/"at" con
 * strings, separan el matching de sell (compras de mayor a menor) y de buy, e
 * imprimen en el orden y formato correctos.
 *
 * OJO: segun mis pruebas esta version NO funciona con el formato del enunciado
 * ("buy 10 shares at 100"). Problemas detectados (ver comentarios en el codigo):
 *   1) La lectura con dos cin.get() consume solo ' ' y 's', luego cin >> int falla.
 *   2) Se imprime sin separador de linea entre ordenes.
 *   3) Se imprime en orden "bid ask stock" cuando el enunciado pide "ask bid stock".
 *   4) ask/bid no se reinician a -1 cuando el mapa queda vacio (quedan valores viejos).
 *   5) Las compras se cruzan de menor a mayor precio, y deberia priorizarse el mayor bid.
 *
 * Complejidad (de la idea, si funcionara): por orden se recorren como mucho los
 * niveles de precio distintos, <= 1000, es decir O(n * P) por caso, con P <= 1000.
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
        // precio -> cantidad total pendiente en ese nivel de precio (ordenado por precio).
        map<int, int> lista_ventas, lista_compras;
        // Valores a imprimir; -1 significa "no definido" (se imprime '-').
        int precio_compra_output = -1, precio_venta_output = -1, precio_stock = -1;
        // aks price: precio menor de venta || bid price: precio mayor de compra || stock price: precio ultima transaccion
        for (int j = 0; j < n; j++){

            string tipo_orden; cin >> tipo_orden;
            int nro_acciones; cin >> nro_acciones;
            // OJO: intenta saltar " shares at " con solo dos cin.get(): consume ' ' y 's'
            // pero queda "hares at y"; el siguiente cin >> int falla (y deja el stream
            // en estado de error). Deberia leerse "shares" y "at" como strings (ver E_LLM).
            cin.get(); cin.get();
            int precio_acciones; cin >> precio_acciones;

            // Se agrega la orden al nivel de precio correspondiente (operator[] crea el
            // nivel en 0 si no existe, y += acumula).
            if (tipo_orden == "sell"){
                lista_ventas[precio_acciones] += nro_acciones;
            }
            //ver que las compras también se efectuen al insertar sell, no solo buy
            
            else if (tipo_orden == "buy") lista_compras[precio_acciones] += nro_acciones;
            
            // Matching: se cruza todo lo cruzable tras la nueva orden (ya sea buy o sell).
            // OJO: las compras se recorren de menor a mayor precio; si llega un sell que
            // cruza con varias compras, deberia atenderse primero la de mayor precio.
            for (auto it_compra = lista_compras.begin(); it_compra != lista_compras.end(); ){
                int precio_compra = it_compra->first;
                int& cantidad_compra = it_compra->second;

                // Solo las ventas con precio <= precio de compra pueden cruzar:
                // TRUCO: upper_bound(precio_compra) delimita el rango con el orden del map.
                for (auto it = lista_ventas.begin(); it != lista_ventas.upper_bound(precio_compra); ){
                    int precio_venta = it->first;
                    int& cantidad_venta = it->second;
                    int transaccion = min(cantidad_compra, cantidad_venta);
                    if (transaccion > 0){
                        // La transaccion se hace al precio del vendedor.
                        precio_stock = precio_venta;
                        cantidad_compra -= transaccion;
                        cantidad_venta -= transaccion;
                    }
                    
                    // Eliminar venta si cantidad = 0 
                    // (erase devuelve el siguiente iterador, valido para continuar el bucle)
                    if (it->second == 0) {
                        it = lista_ventas.erase(it);
                    } else {
                        ++it;
                    }
                }
                
                // Eliminar compra si cantidad = 0
                if (it_compra->second == 0) {
                    it_compra = lista_compras.erase(it_compra);
                } else {
                    ++it_compra;
                }
            }

            // OJO: solo se actualizan si el mapa no esta vacio; si queda vacio conservan
            // el valor de una orden anterior (deberian volver a -1).
            if (!lista_ventas.empty()) {
                precio_venta_output = lista_ventas.begin()->first;  // Ask price (más bajo)
            }
            if (!lista_compras.empty()) {
                precio_compra_output = lista_compras.rbegin()->first;  // Bid price (más alto)
            }
            // OJO: (1) el orden impreso es bid, ask, stock, pero el enunciado pide ask, bid,
            // stock; (2) no hay separador ni salto de linea entre ordenes; (3) el operador
            // ternario mezcla char ('-') e int, ambos se promueven a int, asi que imprimiria
            // el codigo ASCII de '-' (45) en lugar del caracter '-'.
            cout << (precio_compra_output <= 0 ? '-' : precio_compra_output) << ' ' << (precio_venta_output <= 0 ? '-' : precio_venta_output) << ' ' << (precio_stock <= 0 ? '-' : precio_stock);
        }
    }




    return 0;
}
