#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int n, m, l, p, q, r;
    cin >> n >> m >> l >> p >> q >> r;
    cout << max({ (n / p) * (m / q) * (l / r),
            (n / p) * (m / r) * (l / q),
            (n / q) * (m / p) * (l / r),
            (n / q) * (m / r) * (l / p),
            (n / r) * (m / p) * (l / q),
            (n / r) * (m / q) * (l / p) }) << endl;
}
