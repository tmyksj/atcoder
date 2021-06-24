#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<long long> a(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> b(n, a[0] - 1);
    for (int i = 0; i < n - 1; i++) {
        b[i + 1] = b[i] + a[i + 1] - a[i] - 1;
    }

    for (int i = 0; i < q; i++) {
        long long k;
        cin >> k;

        vector<long long>::iterator j = lower_bound(b.begin(), b.end(), k);
        if (j == b.begin()) {
            cout << k << endl;
        } else {
            cout << a[distance(b.begin(), j - 1)] - *(j - 1) + k << endl;
        }
    }
}
