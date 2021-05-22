#include <iostream>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    string t = "";
    for (int i = 0; i < n; i++) {
        string w = "";
        for (int j = 0; j < static_cast<int>(t.size()); j++) {
            if (t[j] != s[i]) {
                w += t[j];
            }
        }

        w += s[i];
        t = w;
    }

    cout << t << endl;
}
