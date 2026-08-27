#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, min = 0, max1 = 0, max2 = 0;
    vector<int> picos;
    cin >> n;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        picos.push_back(x);
        if (x >= max1){
            if ((max1-min) > max2) max2 = (max1-min);
            max1 = x;
            min = x;
        }
        else{
            if (x < min) min = x;
        }
    }
    min = 0; max1 = 0;
    for (int i = picos.size() - 1; i >= 0; i--){
        if (picos[i] >= max1){
            if ((max1-min) > max2) max2 = (max1-min);
            max1 = picos[i];
            min = picos[i];
        }
        else{
            if (picos[i] < min) min = picos[i];
        }
    }

    cout << max2;
    return 0;

}