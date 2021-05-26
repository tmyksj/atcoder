#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m), b(m), c(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    int res = 0;
    for (int i = 0; i < (1 << n); i++) {
        bool r0 = true;
        vector<bool> r1(n, false);
        for (int j = 0; j < m; j++) {
            bool ra = (i & (1 << (a[j] - 1))) > 0;
            bool rb = (i & (1 << (b[j] - 1))) > 0;
            bool rc = (i & (1 << (c[j] - 1))) > 0;
            if (ra && rb && rc) {
                r0 = false;
            } else if (ra && rb) {
                r1[c[j] - 1] = true;
            } else if (ra && rc) {
                r1[b[j] - 1] = true;
            } else if (rb && rc) {
                r1[a[j] - 1] = true;
            }
        }

        if (r0) {
            int c = 0;
            for (int j = 0; j < n; j++) {
                if (r1[j]) {
                    c++;
                }
            }

            res = max(res, c);
        }
    }

    cout << res << endl;
}
