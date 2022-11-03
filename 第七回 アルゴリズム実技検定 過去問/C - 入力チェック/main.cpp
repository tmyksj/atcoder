#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    long long l, r;
    cin >> s >> l >> r;

    long long t = s[0] - '0';
    for (int i = 1; i < static_cast<int>(s.size()); i++) {
        t *= 10;
        t += s[i] - '0';
    }

    cout << ((s == "0" || s[0] != '0') && s.size() <= 10 && l <= t && t <= r ? "Yes" : "No") << endl;
}
