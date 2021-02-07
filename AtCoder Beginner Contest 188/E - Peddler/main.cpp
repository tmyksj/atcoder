#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> x(m), y(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i] >> y[i];
    }

    vector<vector<int>> g(n, vector<int>(0)), h(n, vector<int>(0));
    for (int i = 0; i < m; i++) {
        g[x[i] - 1].push_back(y[i] - 1);
        h[y[i] - 1].push_back(x[i] - 1);
    }

    vector<int> b(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        b[i] = max(b[i], a[i]);
        for (int j = 0; j < static_cast<int>(h[i].size()); j++) {
            b[h[i][j]] = max(b[h[i][j]], b[i]);
        }
    }

    int res = -(1 << 30);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < static_cast<int>(g[i].size()); j++) {
            res = max(res, b[g[i][j]] - a[i]);
        }
    }

    cout << res << endl;
}
