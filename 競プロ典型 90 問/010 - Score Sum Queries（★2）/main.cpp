#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> c(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> p[i];
    }

    int q;
    cin >> q;

    vector<int> l(q), r(q);
    for (int i = 0; i < q; i++) {
        cin >> l[i] >> r[i];
    }

    int m = 2;

    vector<vector<int>> s(m, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        s[c[i] - 1][i + 1] = p[i];
        for (int j = 0; j < m; j++) {
            s[j][i + 1] += s[j][i];
        }
    }

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < m; j++) {
            cout << (j == 0 ? "" : " ") << s[j][r[i]] - s[j][l[i] - 1];
        }
        cout << endl;
    }
}
