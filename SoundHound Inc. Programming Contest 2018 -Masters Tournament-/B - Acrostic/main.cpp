#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    int w;
    cin >> s >> w;

    for (int i = 0; i < static_cast<int>(s.size()); i += w) {
        cout << s[i];
    }
    cout << endl;
}
