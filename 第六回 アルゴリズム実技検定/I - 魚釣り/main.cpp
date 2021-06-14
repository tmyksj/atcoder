#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int h, w;
    cin >> h >> w;

    vector<vector<long long>> a(h, vector<long long>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> a[i][j];
        }
    }

    vector<vector<vector<long long>>> dp(h, vector<vector<long long>>(w, vector<long long>(h + w, 0)));
    dp[0][0][1] = a[0][0];

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < h + w; k++) {
                if (i < h - 1) {
                    dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k]);
                    if (k < h + w - 1) {
                        dp[i + 1][j][k + 1] = max(dp[i + 1][j][k + 1], dp[i][j][k] + a[i + 1][j]);
                    }
                }
                if (j < w - 1) {
                    dp[i][j + 1][k] = max(dp[i][j + 1][k], dp[i][j][k]);
                    if (k < h + w - 1) {
                        dp[i][j + 1][k + 1] = max(dp[i][j + 1][k + 1], dp[i][j][k] + a[i][j + 1]);
                    }
                }
            }
        }
    }

    for (int i = 1; i <= h + w - 1; i++) {
        cout << dp[h - 1][w - 1][i] << endl;
    }
}
