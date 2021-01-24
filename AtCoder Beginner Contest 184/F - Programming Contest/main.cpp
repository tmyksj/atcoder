#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, t;
    cin >> n >> t;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> b((n + 1) / 2);
    for (int i = 0; i < (n + 1) / 2; i++) {
        b[i] = a[i];
    }

    vector<long long> c(n / 2);
    for (int i = 0; i < n / 2; i++) {
        c[i] = a[i + (n + 1) / 2];
    }

    vector<long long> p(1 << b.size());
    for (int i = 0; i < static_cast<int>(p.size()); i++) {
        for (int j = 0; j < static_cast<int>(b.size()); j++) {
            if ((i & (1 << j)) > 0) {
                p[i] += b[j];
            }
        }
    }

    vector<long long> q(1 << c.size());
    for (int i = 0; i < static_cast<int>(q.size()); i++) {
        for (int j = 0; j < static_cast<int>(c.size()); j++) {
            if ((i & (1 << j)) > 0) {
                q[i] += c[j];
            }
        }
    }

    sort(p.begin(), p.end());
    sort(q.begin(), q.end());

    long long res = 0;
    for (int i = 0, j = q.size() - 1; i < static_cast<int>(p.size()); i++) {
        while (j >= 0 && p[i] + q[j] > t) {
            j--;
        }

        if (j >= 0) {
            res = max(res, p[i] + q[j]);
        } else if (p[i] <= t) {
            res = max(res, p[i]);
        }
    }

    cout << res << endl;
}
