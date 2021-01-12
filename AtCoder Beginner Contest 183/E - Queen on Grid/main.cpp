#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int h, w;
    cin >> h >> w;

    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
    }

    vector<vector<int>> t(h + 2, vector<int>(w + 2, 1));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '.') {
                t[i + 1][j + 1] = 0;
            }
        }
    }

    long long mod = 1000000007;

    vector<vector<long long>> a(h + 2, vector<long long>(w + 2, 0)),
            b(h + 2, vector<long long>(w + 2, 0)),
            c(h + 2, vector<long long>(w + 2, 0));

    if (t[1][2] == 0) {
        a[1][2] = 1;
    }

    if (t[2][1] == 0) {
        b[2][1] = 1;
    }

    if (t[2][2] == 0) {
        c[2][2] = 1;
    }

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (t[i][j + 1] == 0) {
                a[i][j + 1] = (a[i][j + 1] + 2 * a[i][j] + b[i][j] + c[i][j]) % mod;
            }

            if (t[i + 1][j] == 0) {
                b[i + 1][j] = (b[i + 1][j] + a[i][j] + 2 * b[i][j] + c[i][j]) % mod;
            }

            if (t[i + 1][j + 1] == 0) {
                c[i + 1][j + 1] = (c[i + 1][j + 1] + a[i][j] + b[i][j] + 2 * c[i][j]) % mod;
            }
        }
    }

    cout << (a[h][w] + b[h][w] + c[h][w]) % mod << endl;
}
