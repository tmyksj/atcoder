#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    int res = 0;
    map<int, int> m;

    for (int i = 0, r = 0; i < n; i++) {
        m[c[i]]++;
        if (m[c[i]] == 1) {
            r++;
        }

        if (i >= k) {
            m[c[i - k]]--;
            if (m[c[i - k]] == 0) {
                r--;
            }
        }

        res = max(res, r);
    }

    cout << res << endl;
}
