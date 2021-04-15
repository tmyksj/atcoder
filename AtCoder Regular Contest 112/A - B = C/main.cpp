#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        long long l, r;
        cin >> l >> r;
        cout << (r - 2 * l >= 0 ? (r - 2 * l + 1) * (r - 2 * l + 2) / 2 : 0) << endl;
    }
}
