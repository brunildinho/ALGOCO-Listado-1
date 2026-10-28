#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set> // ?

using namespace std;

int main() {
    string xinput;
    set<string> outputs;
    vector<string> inputs;

    while (cin >> xinput){
        inputs.push_back(xinput);
    }

    for (int i = 0; i < inputs.size(); i++){
        for(int j = 0; j < inputs.size(); j++){
            if (i != j){
                outputs.insert(inputs[i]+inputs[j]);
            }
        }
    }
    
    for (string output : outputs){
        cout << output << endl;
    }

    return 0;
}