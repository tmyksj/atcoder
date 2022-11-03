#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    int d = 0;

    for (int i = 0; i <= 13; i += 2) {
        d += s[i] - '0';
    }

    d *= 3;

    for (int i = 1; i <= 13; i += 2) {
        d += s[i] - '0';
    }

    d %= 10;

    cout << (s[14] - '0' == d ? "Yes" : "No") << endl;
}
