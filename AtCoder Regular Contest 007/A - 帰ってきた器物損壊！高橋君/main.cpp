#include <iostream>
#include <string>

using namespace std;

int main() {
    string x, s;
    cin >> x >> s;

    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        if (s[i] != x[0]) {
            cout << s[i];
        }
    }
    cout << endl;
}
