#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> b(2 * n + 1, 0);
    for (int i = 1; i <= 2 * n; i++) {
        b[i] = a[(i - 1) % n] + b[i - 1];
    }

    long long s = accumulate(a.begin(), a.end(), 0LL);
    long long res = s;

    for (int i = 1; i <= n; i++) {
        int j = distance(b.begin(), lower_bound(b.begin(), b.end(), b[i - 1] + s / 2));
        res = min(res, abs(2 * b[min(max(0, j - 1), 2 * n)] - 2 * b[i - 1] - s));
        res = min(res, abs(2 * b[min(max(0, j), 2 * n)] - 2 * b[i - 1] - s));
    }

    cout << res << endl;
}
