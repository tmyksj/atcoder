#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    int s = accumulate(t.begin(), t.end(), 0);

    vector<vector<bool>> dp(n + 1, vector<bool>(s + 1, false));
    dp[0][0] = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= s; j++) {
            if (dp[i][j]) {
                dp[i + 1][j] = true;
                dp[i + 1][j + t[i]] = true;
            }
        }
    }

    int res = s;
    for (int i = 0; i <= s; i++) {
        if (dp[n][i]) {
            res = min(res, max(i, s - i));
        }
    }

    cout << res << endl;
}
