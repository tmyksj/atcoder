#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int res = 1 << 30;
    for (int i = 0; i < (1 << (n - 1)); i++) {
        vector<int> b(1, a[0]);
        for (int j = 1; j < n; j++) {
            if ((i & (1 << (j - 1))) > 0) {
                b.push_back(a[j]);
            } else {
                b[b.size() - 1] |= a[j];
            }
        }

        int c = b[0];
        for (int j = 1; j < static_cast<int>(b.size()); j++) {
            c ^= b[j];
        }

        res = min(res, c);
    }

    cout << res << endl;
}
