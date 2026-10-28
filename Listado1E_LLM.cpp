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
                
                for (auto it_venta_iter = lista_ventas.find(precio_acciones); it_venta_iter != lista_ventas.end(); ){
                    int precio_venta = it_venta_iter->first;
                    int& cantidad_venta = it_venta_iter->second;
                    
                    auto it_compra = lista_compras.rbegin();
                    while (it_compra != lista_compras.rend() && cantidad_venta > 0) {
                        if (it_compra->first >= precio_venta) {
                            int& cantidad_compra = const_cast<int&>(it_compra->second);
                            int transaccion = min(cantidad_compra, cantidad_venta);
                            if (transaccion > 0) {
                                precio_stock = precio_venta;
                                cantidad_compra -= transaccion;
                                cantidad_venta -= transaccion;
                            }
                        }
                        ++it_compra;
                    }
                    
                    if (it_venta_iter->second == 0) {
                        it_venta_iter = lista_ventas.erase(it_venta_iter);
                    } else {
                        ++it_venta_iter;
                    }
                }
                
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
            
            precio_venta_output = -1;
            precio_compra_output = -1;
            
            if (!lista_ventas.empty()) {
                precio_venta_output = lista_ventas.begin()->first;
            }
            if (!lista_compras.empty()) {
                precio_compra_output = lista_compras.rbegin()->first;
            }
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
