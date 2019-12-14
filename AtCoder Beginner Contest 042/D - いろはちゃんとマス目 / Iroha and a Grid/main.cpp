#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long h, w, a, b;
    cin >> h >> w >> a >> b;

    long long mod_n = 1000000007;
    vector<long long> inv(h + w + 1, 0), frac(h + w + 1, 0), frac_inv(h + w + 1, 0);
    inv[1] = 1;
    frac[0] = frac[1] = 1;
    frac_inv[0] = frac_inv[1] = 1;
    for (int i = 2; i <= h + w; i++) {
        inv[i] = mod_n - (inv[mod_n % i] * (mod_n / i)) % mod_n;
        frac[i] = (frac[i - 1] * i) % mod_n;
        frac_inv[i] = (frac_inv[i - 1] * inv[i]) % mod_n;
    }

    long long res = 0;
    for (int i = b; i < w; i++) {
        res += ((((frac[(h - a - 1) + i] * frac_inv[h - a - 1]) % mod_n) * frac_inv[i]) % mod_n)
                * ((((frac[(a - 1) + (w - i - 1)] * frac_inv[a - 1]) % mod_n) * frac_inv[w - i - 1]) % mod_n);
        res %= mod_n;
    }

    cout << res << endl;
}
