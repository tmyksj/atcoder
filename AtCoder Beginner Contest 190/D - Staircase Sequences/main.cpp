#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    int res = 0;
    for (long long i = 1; i * (i + 1) / 2 <= n; i++) {
        if ((2 * n - i * i + i) % (2 * i) == 0) {
            res += 2;
        }
    }

    cout << res << endl;
}
