#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, k, q;
    cin >> n >> m >> k >> q;

    vector<int> p(n), t(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> t[i];
    }

    vector<long long> x(1, 0), y(1, 0);
    for (int i = 0; i < n; i++) {
        if (t[i] == 0) {
            x.push_back(p[i]);
        } else {
            y.push_back(p[i]);
        }
    }

    sort(x.begin(), x.end());
    for (int i = 1; i < static_cast<int>(x.size()); i++) {
        x[i] += x[i - 1];
    }

    sort(y.begin(), y.end());
    for (int i = 1; i < static_cast<int>(y.size()); i++) {
        y[i] += y[i - 1];
    }

    long long res = 1LL << 61;
    for (int i = 0; i <= m; i++) {
        if (i < static_cast<int>(x.size()) && m - i < static_cast<int>(y.size())) {
            res = min(res, x[i] + y[m - i] + ((m - i + k - 1) / k) * static_cast<long long>(q));
        }
    }

    cout << res << endl;
}
