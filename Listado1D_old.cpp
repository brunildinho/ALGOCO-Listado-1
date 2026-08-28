#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main (){
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        int l;
        string input1, comando;
        cin >> comando;
        cin >> l;
        cin >> input1;
        cout << "\nL obtenido: " << l << endl;
        cout << "Comando obtenido: " << comando << endl;

        string x;
        stack<int> pila;
        for (int j = 0; j < input1.length(); j++){
            if (input1[j] == '[') continue;
            else if (input1[j] == ']'){
                if (!x.empty()){
                    pila.push(stoi(x));

                    cout << pila.top() << endl;

                    x.clear();
                }
                break;
            }
            else if (input1[j] == ',' && x.length() != 0){
                pila.push(stoi(x));

                cout << pila.top() << endl;

                x.clear();
            }
            else {
                x += input1[j];
            }
        }
        for (int j = 0; j < comando.length(); j++){
            if (comando[j] == 'R'){
                stack<int> pila2;

                cout << "Dando vuelta la pila..." << endl;

                while(!pila.empty()){
                    pila2.push(pila.top());
                    cout << pila2.top() << endl;
                    pila.pop();
                }
                pila = pila2;

            }
            else if (comando[j] == 'D'){
                if (pila.empty()) cout << "error" << endl;
                else {cout << "eliminando..." << pila.top() << endl; pila.pop();}
            }
        }
        cout << '[';
            stack<int> pila2;
            while(!pila.empty()){
                pila2.push(pila.top());
                pila.pop();
            }
            pila = pila2;
            while(!pila.empty()){
                cout << pila.top();
                pila.pop();
                if (!pila.empty()){
                    cout << ',';
                }
            }
        cout << ']' << endl;
    }
    return 0;
}