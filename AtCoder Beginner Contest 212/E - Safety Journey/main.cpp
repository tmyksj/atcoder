#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> u(m), v(m);
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i];
    }

    long long mod = 998244353;

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < m; i++) {
        g[u[i] - 1].push_back(v[i] - 1);
        g[v[i] - 1].push_back(u[i] - 1);
    }

    vector<vector<long long>> dp(k + 1, vector<long long>(n, 0));
    dp[0][0] = 1;

    for (int i = 0; i < k; i++) {
        long long s = accumulate(dp[i].begin(), dp[i].end(), 0LL) % mod;

        for (int j = 0; j < n; j++) {
            dp[i + 1][j] = (dp[i + 1][j] - dp[i][j] + s + mod) % mod;

            for (int l = 0; l < static_cast<int>(g[j].size()); l++) {
                dp[i + 1][g[j][l]] = (dp[i + 1][g[j][l]] - dp[i][j] + mod) % mod;
            }
        }
    }

    cout << dp[k][0] << endl;
}
