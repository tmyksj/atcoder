#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, a;
    cin >> n >> a;

    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(2551, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        vector<vector<long long>> next(n + 1, vector<long long>(2551, 0));
        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= 2500; k++) {
                next[j][k] = dp[j][k];
            }
        }

        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= 2500; k++) {
                next[j + 1][k + x[i]] += dp[j][k];
            }
        }

        dp = next;
    }

    long long res = 0;
    for (int i = 1; i <= n && i * a <= 2500; i++) {
        res += dp[i][i * a];
    }

    cout << res << endl;
}
