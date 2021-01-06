#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> b(a);
    for (int i = 1; i < n; i++) {
        b[i] += b[i - 1];
    }

    vector<long long> c(b);
    for (int i = 1; i < n; i++) {
        c[i] += c[i - 1];
    }

    vector<long long> d(b);
    for (int i = 1; i < n; i++) {
        d[i] = max(d[i], d[i - 1]);
    }

    long long res = max(c[0], 0LL);
    for (int i = 1; i < n; i++) {
        res = max(res, c[i]);
        res = max(res, c[i - 1] + d[i]);
    }

    cout << res << endl;
}
