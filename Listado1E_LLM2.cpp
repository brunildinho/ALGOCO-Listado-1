#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        int n; cin >> n;
        map<int, int> lista_ventas, lista_compras;
        int precio_compra_output = -1, precio_venta_output = -1, precio_stock = -1;
        // aks price: precio menor de venta || bid price: precio mayor de compra || stock price: precio ultima transaccion
        for (int j = 0; j < n; j++){

            string tipo_orden, shares_word, at_word;
            int nro_acciones, precio_acciones;
            cin >> tipo_orden >> nro_acciones >> shares_word >> at_word >> precio_acciones;

            if (tipo_orden == "sell"){
                lista_ventas[precio_acciones] += nro_acciones;
                
                // Matching: buscar todas las compras con precio >= precio_venta
                auto it_compra = lista_compras.rbegin();
                while (it_compra != lista_compras.rend() && lista_ventas[precio_acciones] > 0) {
                    if (it_compra->first >= precio_acciones) {
                        int transaccion = min(it_compra->second, lista_ventas[precio_acciones]);
                        it_compra->second -= transaccion;
                        lista_ventas[precio_acciones] -= transaccion;
                        precio_stock = precio_acciones;
                    }
                    ++it_compra;
                }
            }
            else if (tipo_orden == "buy"){
                lista_compras[precio_acciones] += nro_acciones;
                
                // Matching: buscar todas las ventas con precio <= precio_compra
                for (auto it = lista_ventas.begin(); it != lista_ventas.end() && lista_compras[precio_acciones] > 0; ){
                    if (it->first <= precio_acciones) {
                        int transaccion = min(it->second, lista_compras[precio_acciones]);
                        it->second -= transaccion;
                        lista_compras[precio_acciones] -= transaccion;
                        precio_stock = it->first;
                    }
                    
                    if (it->second == 0) {
                        it = lista_ventas.erase(it);
                    } else {
                        ++it;
                    }
                }
            }

            // Limpiar órdenes completadas
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
            precio_venta_output = lista_ventas.empty() ? -1 : lista_ventas.begin()->first;
            precio_compra_output = lista_compras.empty() ? -1 : lista_compras.rbegin()->first;
            
            cout << (precio_venta_output <= 0 ? "-" : to_string(precio_venta_output)) << ' ' 
                 << (precio_compra_output <= 0 ? "-" : to_string(precio_compra_output)) << ' ' 
                 << (precio_stock <= 0 ? "-" : to_string(precio_stock)) << '\n';
        }
    }




    return 0;
}