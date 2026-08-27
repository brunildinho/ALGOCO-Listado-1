#include <iostream>
#include <list>
#include <string>
#include <limits>

using namespace std;

int main(){
    int t; //Usar lista doble enlazada? 
    cin >> t;
    cin.get();

    for (int i = 0; i < t; i++){
        string linea;
        getline(cin, linea);
        bool endline = true;
        
        list<char> caracteres;
        for (char x : linea){
            if (x == '[') {endline = false;}
            else if (x == ']') {endline = true;}
            else if (x == '<') {if (endline == true && !caracteres.empty()) caracteres.pop_back();}
            else {
                if (endline) caracteres.push_back(x);
                else caracteres.push_front(x);
            }
        }

        for (char x : caracteres){
            cout << x;
        }
        
        cout << endl;
    }
    return 0;
}