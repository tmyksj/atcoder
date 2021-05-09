#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n, q;
    string s;
    cin >> n >> s >> q;

    vector<int> t(q), a(q), b(q);
    for (int i = 0; i < q; i++) {
        cin >> t[i] >> a[i] >> b[i];
    }

    string res = s;

    int p = 0;
    for (int i = 0; i < q; i++) {
        if (t[i] == 1) {
            swap(res[(a[i] + p * n - 1) % (2 * n)], res[(b[i] + p * n - 1) % (2 * n)]);
        } else {
            p = (p + 1) % 2;
        }
    }
    if (p == 1) {
        for (int i = 0; i < n; i++) {
            swap(res[i], res[i + n]);
        }
    }

    cout << res << endl;
}
