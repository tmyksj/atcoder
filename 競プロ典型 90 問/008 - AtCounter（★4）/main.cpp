#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    string t = "atcoder";

    long long mod = 1000000007;

    vector<vector<long long>> dp(n, vector<long long>(t.size(), 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < static_cast<int>(t.size()); j++) {
            if (i == 0 && j == 0 && s[i] == t[j]) {
                dp[i][j] = 1;
            } else if (i > 0 && j == 0 && s[i] == t[j]) {
                dp[i][j] = (dp[i - 1][j] + 1) % mod;
            } else if (i > 0 && s[i] == t[j]) {
                dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % mod;
            } else if (i > 0) {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    cout << dp[n - 1][t.size() - 1] << endl;
}
