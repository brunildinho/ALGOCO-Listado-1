#include <iostream>
#include <set>

using namespace std;

int main(){
    int n, y;
    set<int> obstaculos;
    cin >> n;
    cin >> y;
    for (int i = 0; i < y; i++){
        int x;
        cin >> x;
        obstaculos.insert(x);
    }

    for (int i = 0; i < n; i++){
        if (obstaculos.count(i) == 0){
            cout << i << endl;
        }
    }
    cout << "Mario got "<< obstaculos.size() <<" of the dangerous obstacles." << endl;
    
}
