#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long solve(int n, long long x, vector<long long>& a, int m) {
    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(m + 1, vector<long long>(m, -1)));
    dp[0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                if (dp[i][j][k] >= 0) {
                    dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k]);
                    dp[i + 1][j + 1][(k + a[i]) % m] = max(dp[i + 1][j + 1][(k + a[i]) % m], dp[i][j][k] + a[i]);
                }
            }
        }
        for (int k = 0; k < m; k++) {
            if (dp[i][m][k] > 0) {
                dp[i + 1][m][k] = max(dp[i + 1][m][k], dp[i][m][k]);
            }
        }
    }

    if (dp[n][m][x % m] >= 0) {
        return (x - dp[n][m][x % m]) / m;
    } else {
        return 1LL << 61;
    }
}

int main() {
    int n;
    long long x;
    cin >> n >> x;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long res = 1LL << 61;
    for (int i = 0; i < n; i++) {
        res = min(res, solve(n, x, a, i + 1));
    }

    cout << res << endl;
}
