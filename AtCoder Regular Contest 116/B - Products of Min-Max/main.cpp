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

    long long mod = 998244353;
    sort(a.begin(), a.end());

    long long res = a[0] * a[0] % mod, p = a[0];
    for (int i = 1; i < n; i++) {
        res = (res + a[i] * (a[i] + p)) % mod;
        p = (2 * p + a[i]) % mod;
    }

    cout << res << endl;
}
