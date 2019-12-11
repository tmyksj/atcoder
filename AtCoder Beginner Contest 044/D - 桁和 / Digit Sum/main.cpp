#include <iostream>

using namespace std;

long long f(long long b, long long n) {
    return b <= n ? f(b, n / b) + n % b : n;
}

int main() {
    long long n, s;
    cin >> n >> s;

    long long res = -1;

    long long b = 2;
    for (; (b - 1) * (b - 1) <= n; b++) {
        if (f(b, n) == s) {
            res = b;
            goto out;
        }
    }

    for (; b > 0; b--) {
        if ((n - s + b) % b == 0
                && b < (n - s + b) / b
                && 0 <= s - b
                && s - b < (n - s + b) / b) {
            res = (n - s + b) / b;
            goto out;
        }
    }

    if (n == s) {
        res = n + 1;
    }

out:
    cout << res << endl;
}
