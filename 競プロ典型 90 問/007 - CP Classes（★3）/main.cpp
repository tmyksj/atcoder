#include <algorithm>
#include <iterator>
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

    int q;
    cin >> q;

    vector<int> b(q);
    for (int i = 0; i < q; i++) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());

    vector<int> res(q);
    for (int i = 0; i < q; i++) {
        int j = distance(a.begin(), lower_bound(a.begin(), a.end(), b[i]));

        if (j == 0) {
            res[i] = a[j] - b[i];
        } else if (j < n) {
            res[i] = min(b[i] - a[j - 1], a[j] - b[i]);
        } else {
            res[i] = b[i] - a[j - 1];
        }
    }

    for (int i = 0; i < q; i++) {
        cout << res[i] << endl;
    }
}
