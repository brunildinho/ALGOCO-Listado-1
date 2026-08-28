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
        bool flag_error = false, reversed = false;
        cin >> comando;
        cin >> l;
        cin >> input1;

        /*
        cout << "\nL obtenido: " << l << endl;
        cout << "Comando obtenido: " << comando << endl;
        */

        string x;
        deque<int> pila;
        for (int j = 0; j < input1.length(); j++){
            if (input1[j] == '[') continue;
            else if (input1[j] == ']'){
                if (!x.empty()){
                    pila.push_back(stoi(x));

                    //cout << pila.back() << endl;

                    x.clear();
                }
                break;
            }
            else if (input1[j] == ',' && x.length() != 0){
                pila.push_back(stoi(x));

                //cout << pila.back() << endl;

                x.clear();
            }
            else {
                x += input1[j];
            }
        }
        for (int j = 0; j < comando.length(); j++){
            if (comando[j] == 'R'){
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
                    if (!reversed) pila.pop_front();
                    else pila.pop_back();
                }
            }
        }

        if (flag_error) continue;

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