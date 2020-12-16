#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n, l;
    cin >> n >> l;

    vector<string> s(l + 1);
    getline(cin, s[0]);

    for (int i = 0; i < l + 1; i++) {
        getline(cin, s[i]);
    }

    int p = -1;
    for (int i = 0; i < 2 * n - 1; i += 2) {
        if (s[l][i] == 'o') {
            p = i;
        }
    }

    for (int i = l - 1; i >= 0; i--) {
        if (p > 0 && s[i][p - 1] == '-') {
            p -= 2;
        } else if (p < 2 * n - 2 && s[i][p + 1] == '-') {
            p += 2;
        }
    }

    cout << p / 2 + 1 << endl;
}
