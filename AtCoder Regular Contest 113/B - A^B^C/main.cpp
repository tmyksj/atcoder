#include <iostream>

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
    long long a, b, c;
    cin >> a >> b >> c;

    long long p[] = { 1, 1, 4, 4, 2, 1, 1, 4, 4, 2 };
    long long q = pow_mod(b, c, p[a % 10]);
    cout << pow_mod(a, q == 0 ? p[a % 10] : q, 10LL) << endl;
}
