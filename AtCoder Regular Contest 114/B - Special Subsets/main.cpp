#include <iostream>
#include <vector>

using namespace std;

template <class T>
T pow_mod(T a, T b, T mod) {
    T r = 1;
    for (T i = 1, j = a; i <= b; i <<= 1, j = (j * j) % mod) {
        if ((i & b) > 0) {
            r = (r * j) % mod;
        }
    }
    return r;
}

int main() {
    int n;
    cin >> n;

    vector<int> f(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }

    long long p = 0;
    vector<int> q(n, -1);
    for (int i = 0; i < n; i++) {
        int j = i;
        for (; q[j] == -1; j = f[j] - 1) {
            q[j] = i;
        }

        if (q[j] == i) {
            p++;
        }
    }

    long long m = 998244353;
    cout << (pow_mod(2LL, p, m) + m - 1) % m << endl;
}
