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

            string tipo_orden; cin >> tipo_orden;
            int nro_acciones; cin >> nro_acciones;
            cin.get(); cin.get();
            int precio_acciones; cin >> precio_acciones;

            if (tipo_orden == "sell"){
                lista_ventas[precio_acciones] += nro_acciones;
            }
            //ver que las compras también se efectuen al insertar sell, no solo buy
            
            else if (tipo_orden == "buy") lista_compras[precio_acciones] += nro_acciones;
            
            for (auto it_compra = lista_compras.begin(); it_compra != lista_compras.end(); ){
                int precio_compra = it_compra->first;
                int& cantidad_compra = it_compra->second;

                for (auto it = lista_ventas.begin(); it != lista_ventas.upper_bound(precio_compra); ){
                    int precio_venta = it->first;
                    int& cantidad_venta = it->second;
                    int transaccion = min(cantidad_compra, cantidad_venta);
                    if (transaccion > 0){
                        precio_stock = precio_venta;
                        cantidad_compra -= transaccion;
                        cantidad_venta -= transaccion;
                    }
                    
                    // Eliminar venta si cantidad = 0 
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

            if (!lista_ventas.empty()) {
                precio_venta_output = lista_ventas.begin()->first;  // Ask price (más bajo)
            }
            if (!lista_compras.empty()) {
                precio_compra_output = lista_compras.rbegin()->first;  // Bid price (más alto)
            }
            cout << (precio_compra_output <= 0 ? '-' : precio_compra_output) << ' ' << (precio_venta_output <= 0 ? '-' : precio_venta_output) << ' ' << (precio_stock <= 0 ? '-' : precio_stock);
        }
    }




    return 0;
}
