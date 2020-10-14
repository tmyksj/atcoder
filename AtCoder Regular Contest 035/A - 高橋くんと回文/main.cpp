#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    bool res = true;
    for (int i = 0, n = s.size(); i < n / 2; i++) {
        res = res && (s[i] == s[n - i - 1] || s[i] == '*' || s[n - i - 1] == '*');
    }

    cout << (res ? "YES" : "NO") << endl;
}
