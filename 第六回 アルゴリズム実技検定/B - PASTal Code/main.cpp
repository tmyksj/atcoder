#include <iostream>

using namespace std;

int main() {
    string s;
    cin >> s;

    int p = -1;
    for (int i = 0; i < static_cast<int>(s.size()); i += 4) {
        if (s[i] == 'p' && s[i + 1] == 'o' && s[i + 2] == 's' && s[i + 3] == 't') {
            p = i / 4;
            break;
        }
    }

    if (p == -1) {
        cout << "none" << endl;
    } else {
        cout << p + 1 << endl;
    }
}
