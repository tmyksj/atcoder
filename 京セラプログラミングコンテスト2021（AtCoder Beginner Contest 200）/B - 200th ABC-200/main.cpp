#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    long long res = n;
    for (int i = 0; i < k; i++) {
        if (res % 200 == 0) {
            res /= 200;
        } else {
            res = 1000 * res + 200;
        }
    }

    cout << res << endl;
}
