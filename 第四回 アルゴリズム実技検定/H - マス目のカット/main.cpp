#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<vector<vector<int>>> t(n + 1, vector<vector<int>>(m + 1, vector<int>(10, 0)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            t[i + 1][j + 1][s[i][j] - '0']++;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int l = 0; l < 10; l++) {
                t[i][j][l] += t[i][j - 1][l];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int l = 0; l < 10; l++) {
                t[i][j][l] += t[i - 1][j][l];
            }
        }
    }

    int r = min(n, m);
    for (; ; r--) {
        for (int i = r; i <= n; i++) {
            for (int j = r; j <= m; j++) {
                int v = 0;
                for (int l = 0; l < 10; l++) {
                    v = max(v, t[i][j][l] - t[i][j - r][l] - t[i - r][j][l] + t[i - r][j - r][l]);
                }

                if (r * r - v <= k) {
                    goto out;
                }
            }
        }
    }

out:
    cout << r << endl;
}
