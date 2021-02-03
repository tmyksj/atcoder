#include <iostream>
#include <vector>

using namespace std;

void dfs_a(vector<vector<int>>& g, vector<int>& d, int i, int v) {
    d[i] = v;

    for (int j = 0; j < static_cast<int>(g[i].size()); j++) {
        if (d[g[i][j]] == -1) {
            dfs_a(g, d, g[i][j], v + 1);
        }
    }
}

void dfs_b(vector<vector<int>>& g, vector<long long>& c, int i, long long v, vector<bool>& w) {
    c[i] += v;
    w[i] = false;

    for (int j = 0; j < static_cast<int>(g[i].size()); j++) {
        if (w[g[i][j]]) {
            dfs_b(g, c, g[i][j], c[i], w);
        }
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n - 1), b(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i] >> b[i];
        a[i]--;
        b[i]--;
    }

    int q;
    cin >> q;

    vector<int> t(q), e(q);
    vector<long long> x(q);
    for (int i = 0; i < q; i++) {
        cin >> t[i] >> e[i] >> x[i];
        e[i]--;
    }

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < n - 1; i++) {
        g[a[i]].push_back(b[i]);
        g[b[i]].push_back(a[i]);
    }

    vector<int> d(n, -1);
    dfs_a(g, d, 0, 0);

    vector<long long> c(n, 0);
    for (int i = 0; i < q; i++) {
        if (t[i] == 1) {
            if (d[a[e[i]]] < d[b[e[i]]]) {
                c[0] += x[i];
                c[b[e[i]]] -= x[i];
            } else {
                c[a[e[i]]] += x[i];
            }
        } else {
            if (d[a[e[i]]] < d[b[e[i]]]) {
                c[b[e[i]]] += x[i];
            } else {
                c[0] += x[i];
                c[a[e[i]]] -= x[i];
            }
        }
    }

    vector<bool> w(n, true);
    dfs_b(g, c, 0, 0, w);

    for (int i = 0; i < n; i++) {
        cout << c[i] << endl;
    }
}
