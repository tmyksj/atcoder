#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;

    string t = "chokudai";
    long long mod = 1000000007;

    vector<vector<long long>> dp(s.size() + 1, vector<long long>(t.size() + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        for (int j = 0; j < static_cast<int>(t.size()); j++) {
            dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % mod;

            if (s[i] == t[j]) {
                dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % mod;
            }
        }

        dp[i + 1][t.size()] = (dp[i + 1][t.size()] + dp[i][t.size()]) % mod;
    }

    cout << dp[s.size()][t.size()] << endl;
}
