#include <iostream>

using namespace std;

int main() {
    long long a, b, c;
    cin >> a >> b >> c;

    long long mod = 998244353;

    long long res = a * (a + 1) / 2 % mod;
    res *= b * (b + 1) / 2 % mod; res %= mod;
    res *= c * (c + 1) / 2 % mod; res %= mod;

    cout << res << endl;
}
