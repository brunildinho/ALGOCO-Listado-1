#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main(){
    int n, k; // N: Nro estudiantes; K: nro de comandos llamados
    stack<int> ordenes;
    cin >> n; //tamaño
    cin >> k; //ordenes
    int p = 0;


    for (int i = 0; i < k; i++){
        string x;
        cin >> x;
        if (x == "undo"){
            cin >> x;
            int undos;
            undos = stoi(x);
            for (int j = 0; j < undos; j++){
                p = (p + (-ordenes.top() % n) + n) % n;
                ordenes.pop();
            }
        }
        else{
            int jumps = stoi(x);
            p = ((p + jumps) % n + n) % n; //Normalización mala 
            ordenes.push(jumps);   
        }
    }
    cout << p << endl;
}