#include <iostream>
#include <string>

using namespace std;

int main() {
    for (int i = 0; i < 3; i++) {
        string s;
        cin >> s;
        cout << s[i];
    }
    cout << endl;
}
