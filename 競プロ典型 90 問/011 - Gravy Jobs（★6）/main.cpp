#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> d(n), c(n);
    vector<long long> s(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i] >> c[i] >> s[i];
    }

    int d_max = *max_element(d.begin(), d.end());

    vector<tuple<int, int, long long>> t(n);
    for (int i = 0; i < n; i++) {
        t[i] = make_tuple(d[i], c[i], s[i]);
    }

    sort(t.begin(), t.end());

    vector<vector<long long>> dp(n + 1, vector<long long>(d_max + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= d_max; j++) {
            if (get<1>(t[i]) <= j && j <= get<0>(t[i])) {
                dp[i + 1][j] = max(dp[i][j], dp[i][j - get<1>(t[i])] + get<2>(t[i]));
            } else {
                dp[i + 1][j] = dp[i][j];
            }
        }
    }

    cout << *max_element(dp[n].begin(), dp[n].end()) << endl;
}
