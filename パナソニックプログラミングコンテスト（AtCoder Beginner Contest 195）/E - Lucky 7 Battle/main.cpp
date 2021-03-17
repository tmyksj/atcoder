#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int b = 7;

    int n;
    string s, x;
    cin >> n >> s >> x;

    vector<vector<int>> g(n, vector<int>(b)), h(n, vector<int>(b));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < b; j++) {
            g[i][j] = 10 * j % b;
            h[i][j] = (10 * j + s[i] - '0') % b;
        }
    }

    vector<vector<bool>> r(n + 1, vector<bool>(b, false));
    r[n][0] = true;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < b; j++) {
            if (x[i] == 'A') {
                r[i][j] = r[i + 1][g[i][j]] && r[i + 1][h[i][j]];
            } else {
                r[i][j] = r[i + 1][g[i][j]] || r[i + 1][h[i][j]];
            }
        }
    }

    cout << (r[0][0] ? "Takahashi" : "Aoki") << endl;
}
