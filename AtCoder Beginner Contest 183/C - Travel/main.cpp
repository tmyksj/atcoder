#include <iostream>
#include <vector>

using namespace std;

int solve(int n, int k, vector<vector<int>>& t, int p, int q, int r) {
    if (p == (1 << n) - 2) {
        return r + t[q][0] == k ? 1 : 0;
    }

    int s = 0;
    for (int i = 1; i < n; i++) {
        if ((p & (1 << i)) == 0) {
            s += solve(n, k, t, p | (1 << i), i, r + t[q][i]);
        }
    }

    return s;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> t(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> t[i][j];
        }
    }

    cout << solve(n, k, t, 0, 0, 0) << endl;
}
