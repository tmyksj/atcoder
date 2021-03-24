#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> t[i];
    }

    int q;
    cin >> q;

    vector<long long> x(q);
    for (int i = 0; i < q; i++) {
        cin >> x[i];
    }

    long long p1 = 0, p2 = -(1LL << 61), p3 = 1LL << 61;
    for (int i = 0; i < n; i++) {
        if (t[i] == 1) {
            p1 += a[i];
            p2 += a[i];
            p3 += a[i];
        }

        if (t[i] == 2) {
            p2 = max(p2, a[i]);
            p3 = max(p3, a[i]);
        }

        if (t[i] == 3) {
            p2 = min(p2, a[i]);
            p3 = min(p3, a[i]);
        }
    }

    for (int i = 0; i < q; i++) {
        cout << min(max(p2, x[i] + p1), p3) << endl;
    }
}
