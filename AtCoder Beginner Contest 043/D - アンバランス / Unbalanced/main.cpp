#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    int a = -1, b = -1, n = s.size();
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            a = i + 1;
            b = i + 2;
            goto out;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1] || s[i + 1] == s[i + 2] || s[i + 2] == s[i]) {
            a = i + 1;
            b = i + 3;
            goto out;
        }
    }

out:
    cout << a << " " << b << endl;
}
