#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    long long res = 0;
    for (long long i = 10, j = 0; i <= 10 * n; i *= 10, j++) {
        res += (min(i - 1, n) - (i / 10) + 1) * (j / 3);
    }

    cout << res << endl;
}
