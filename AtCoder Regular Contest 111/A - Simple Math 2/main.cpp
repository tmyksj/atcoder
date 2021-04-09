#include <iostream>

using namespace std;

long long pow_mod(long long a, long long b, long long mod) {
    long long r = 1;
    for (long long i = 1, j = a; i <= b; i <<= 1, j = (j * j) % mod) {
        if ((i & b) > 0) {
            r = (r * j) % mod;
        }
    }
    return r;
}

int main() {
    long long n, m;
    cin >> n >> m;
    cout << pow_mod(10, n, m * m) / m % m << endl;
}
