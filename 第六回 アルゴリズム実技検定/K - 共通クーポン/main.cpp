#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int a = 100;
    int b = 20;

    int n;
    cin >> n;

    vector<int> p(n), u(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> u[i];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(a, -(1LL << 61)));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < a; j++) {
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            dp[i + 1][(j + p[i]) % a] = max(dp[i + 1][(j + p[i]) % a], dp[i][j] - p[i] + u[i] + (j + p[i]) / a * b);
        }
    }

    cout << *max_element(dp[n].begin(), dp[n].end()) << endl;
}
