#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    int res = 1 << 29;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res = min(res, i == j ? a[i] + b[j] : max(a[i], b[j]));
        }
    }

    cout << res << endl;
}
