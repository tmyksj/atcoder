#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    long long l = 1LL, r = 1414213562LL;
    while (l < r) {
        long long m = (l + r + 1) / 2;
        if (m * (m + 1) / 2 <= n + 1) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    cout << n - l + 1 << endl;
}
