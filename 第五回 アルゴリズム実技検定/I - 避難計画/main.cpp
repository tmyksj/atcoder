#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    vector<int> c(k);
    for (int i = 0; i < k; i++) {
        cin >> c[i];
    }

    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < m; i++) {
        if (h[a[i] - 1] < h[b[i] - 1]) {
            g[a[i] - 1].push_back(b[i] - 1);
        } else {
            g[b[i] - 1].push_back(a[i] - 1);
        }
    }

    vector<tuple<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = make_tuple(h[i], i);
    }

    sort(v.begin(), v.end());

    int inf = 1 << 29;

    vector<int> res(n, inf);
    for (int i = 0; i < k; i++) {
        res[c[i] - 1] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < static_cast<int>(g[get<1>(v[i])].size()); j++) {
            res[g[get<1>(v[i])][j]] = min(res[g[get<1>(v[i])][j]], res[get<1>(v[i])] + 1);
        }
    }

    for (int i = 0; i < n; i++) {
        if (res[i] < inf) {
            cout << res[i] << endl;
        } else {
            cout << "-1" << endl;
        }
    }
}
