#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    long long res = 0;
    for (int i = max(k + 2, 2); i <= min(k + 2 * n, 2 * n); i++) {
        res += static_cast<long long>(min(i - 1, n) - max(i - n, 1) + 1) * (min(i - k - 1, n) - max(i - k - n, 1) + 1);
    }

    cout << res << endl;
}
