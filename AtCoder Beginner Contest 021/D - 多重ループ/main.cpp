#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class nck {
    vector<long long> inv;
    vector<long long> frac;
    vector<long long> frac_inv;
    int mod;

public:
    nck(int n, int m) {
        inv = vector<long long>(n + 1, 0);
        frac = vector<long long>(n + 1, 0);
        frac_inv = vector<long long>(n + 1, 0);
        mod = m;

        inv[1] = 1;
        frac[0] = frac[1] = 1;
        frac_inv[0] = frac_inv[1] = 1;
        for (int i = 2; i <= n; i++) {
            inv[i] = mod - (inv[mod % i] * (mod / i)) % mod;
            frac[i] = (frac[i - 1] * i) % mod;
            frac_inv[i] = (frac_inv[i - 1] * inv[i]) % mod;
        }
    }

    int calc(int n, int k) {
        return (frac[n] * frac_inv[k] % mod) * frac_inv[n - k] % mod;
    }
};

int main() {
    long long n, k;
    cin >> n >> k;

    long long mod = 1000000007;
    nck nck(max(n, k), mod);

    long long res = 0;
    for (int i = 1; i <= n && i <= k; i++) {
        res += static_cast<long long>(nck.calc(n, i)) * nck.calc(k - 1, i - 1);
        res %= mod;
    }

    cout << res << endl;
}
