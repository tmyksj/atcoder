#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> x(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> c[i];
    }

    long long inf = 1LL << 61;

    vector<vector<long long>> y(n + 2, { inf, -inf });
    y[0][0] = y[0][1] = 0;
    for (int i = 0; i < n; i++) {
        y[c[i]][0] = min(y[c[i]][0], x[i]);
        y[c[i]][1] = max(y[c[i]][1], x[i]);
    }
    y[n + 1][0] = y[n + 1][1] = 0;

    vector<vector<long long>> dp(n + 2, vector<long long>(2, inf));
    dp[0][0] = 0;
    dp[0][1] = 0;
    for (int i = 1, j = 0; i <= n + 1; i++) {
        if (y[i][0] > y[i][1]) {
            continue;
        }

        dp[i][0] = min(dp[j][0] + abs(y[j][0] - y[i][1]) + y[i][1] - y[i][0],
                dp[j][1] + abs(y[j][1] - y[i][1]) + y[i][1] - y[i][0]);
        dp[i][1] = min(dp[j][0] + abs(y[j][0] - y[i][0]) + y[i][1] - y[i][0],
                dp[j][1] + abs(y[j][1] - y[i][0]) + y[i][1] - y[i][0]);

        j = i;
    }

    cout << dp[n + 1][0] << endl;
}
