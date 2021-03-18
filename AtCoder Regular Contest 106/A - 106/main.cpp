#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    int a = -1, b = -1;
    for (long long i = 1, p = 3; p <= n; i++, p *= 3) {
        for (long long j = 1, q = 5; p + q <= n; j++, q *= 5) {
            if (p + q == n) {
                a = i;
                b = j;
                goto out;
            }
        }
    }

out:
    if (a == -1) {
        cout << "-1" << endl;
    } else {
        cout << a << " " << b << endl;
    }
}
