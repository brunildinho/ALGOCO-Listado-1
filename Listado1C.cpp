#include <iostream>
#include <list>
#include <string>
#include <limits>
#include <vector>

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
        vector<char> frontline;
        for (char x : linea){
            if (x == '[') {
                if (!frontline.empty()){
                    for (int j = frontline.size() - 1; j >= 0; j--){
                        caracteres.push_front(frontline[j]);
                    }
                }
                frontline.clear();
                endline = false;
            }
            else if (x == ']') {
                if (!frontline.empty()){
                    for (int j = frontline.size() - 1; j >= 0; j--){
                        caracteres.push_front(frontline[j]);
                    }
                }
                frontline.clear();
                endline = true;
            }
            else if (x == '<') {
                if (endline && !caracteres.empty()) caracteres.pop_back();
                else if (!endline && !frontline.empty()) frontline.pop_back();
            }
            else {
                if (endline) caracteres.push_back(x);
                else {
                    frontline.push_back(x);
                }
            }
        }
        
        if (!frontline.empty()) {
            for (int j = frontline.size() - 1; j >= 0; j--){
                caracteres.push_front(frontline[j]);
            }
        }

        for (char x : caracteres){
            cout << x;
        }
        cout << endl;
    }
    return 0;
}