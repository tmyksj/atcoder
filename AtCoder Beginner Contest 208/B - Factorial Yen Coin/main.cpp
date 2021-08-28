#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 10;

    long long p;
    cin >> p;

    vector<long long> f(n + 1, 1LL);
    for (int i = 2; i <= n; i++) {
        f[i] *= f[i - 1] * i;
    }

    int res = 0;
    for (int i = n; i >= 1; i--) {
        if (p >= f[i]) {
            res += p / f[i];
            p %= f[i];
        }
    }

    cout << res << endl;
}
