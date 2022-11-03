#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int s = accumulate(a.begin(), a.end(), 0);

    vector<vector<vector<double>>> dp(n, vector<vector<double>>(s + 1, vector<double>(s + 1, 1 << 29)));
    dp[0][0][0] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j <= s; j++) {
            for (int k = 0; k <= s; k++) {
                for (int l = 0; k + l <= s; l++) {
                    dp[i + 1][l][k + l] = min(dp[i + 1][l][k + l], dp[i][j][k] + sqrt((j - l) * (j - l) + 1));
                }
            }
        }
    }

    cout << setprecision(12) << fixed << dp[n - 1][0][s] << endl;
}
