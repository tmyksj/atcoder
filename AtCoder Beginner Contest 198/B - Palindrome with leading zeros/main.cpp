#include <iostream>
#include <string>

using namespace std;

int main() {
    string n;
    cin >> n;

    string s(n.rbegin(), n.rend());
    for (int i = n.size() - 1; i >= 0 && n[i] == '0'; i--) {
        s += "0";
    }

    string t(s.rbegin(), s.rend());

    cout << (s == t ? "Yes" : "No") << endl;
}
