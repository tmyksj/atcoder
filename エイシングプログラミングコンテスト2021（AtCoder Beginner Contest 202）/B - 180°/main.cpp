#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    string t = "";
    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        if (s[i] == '6') {
            t += '9';
        } else if (s[i] == '9') {
            t += '6';
        } else {
            t += s[i];
        }
    }

    reverse(t.begin(), t.end());
    cout << t << endl;
}
