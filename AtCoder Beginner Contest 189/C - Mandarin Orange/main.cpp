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

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i, k = 1 << 29; j < n; j++) {
            k = min(k, a[j]);
            res = max(res, (j - i + 1) * k);
        }
    }

    cout << res << endl;
}
