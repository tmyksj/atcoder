#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }

    int k;
    cin >> k;

    vector<int> c(k), d(k);
    for (int i = 0; i < k; i++) {
        cin >> c[i] >> d[i];
    }

    int res = 0;
    for (int i = 0; i < (1 << k); i++) {
        vector<int> s(n + 1, 0);
        for (int j = 0; j < k; j++) {
            if ((i & (1 << j)) == 0) {
                s[c[j]]++;
            } else {
                s[d[j]]++;
            }
        }

        int t = 0;
        for (int j = 0; j < m; j++) {
            if (s[a[j]] > 0 && s[b[j]] > 0) {
                t++;
            }
        }

        res = max(res, t);
    }

    cout << res << endl;
}
