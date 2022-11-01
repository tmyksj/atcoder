#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    sort(b.begin(), b.end());

    int res = 1000000000;
    for (int i = 0; i < n; i++) {
        int j = distance(b.begin(), lower_bound(b.begin(), b.end(), a[i]));

        if (j == 0) {
            res = min({ res, b[j] - a[i] });
        } else if (j < m) {
            res = min({ res, a[i] - b[j - 1], b[j] - a[i] });
        } else {
            res = min({ res, a[i] - b[j - 1] });
        }
    }

    cout << res << endl;
}
