#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m), b(m);
    vector<long long> c(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    long long inf = 1LL << 61;

    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(n, vector<long long>(n, inf)));
    for (int i = 0; i < n; i++) {
        dp[0][i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        dp[0][a[i] - 1][b[i] - 1] = c[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                dp[i + 1][j][k] = min(dp[i][j][k], dp[i][j][i] + dp[i][i][k]);
            }
        }
    }

    long long res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (dp[i][j][k] < inf) {
                    res += dp[i][j][k];
                }
            }
        }
    }

    cout << res << endl;
}
