#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    bool res = true;
    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        res = res && ((i % 2 == 0 && 'a' <= s[i] && s[i] <= 'z') || (i % 2 == 1 && 'A' <= s[i] && s[i] <= 'Z'));
    }

    cout << (res ? "Yes" : "No") << endl;
}
