#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void dfs(const vector<vector<int>>& g, int p, int q, vector<int>& r) {
    r.push_back(q);

    for (int i = 0; i < static_cast<int>(g[q].size()); i++) {
        if (g[q][i] != p) {
            dfs(g, q, g[q][i], r);
            r.push_back(q);
        }
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n - 1), b(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i] >> b[i];
    }

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < n - 1; i++) {
        g[a[i] - 1].push_back(b[i] - 1);
        g[b[i] - 1].push_back(a[i] - 1);
    }

    for (int i = 0; i < n; i++) {
        sort(g[i].begin(), g[i].end());
    }

    vector<int> r(0);
    dfs(g, -1, 0, r);

    for (int i = 0; i < static_cast<int>(r.size()); i++) {
        cout << (i == 0 ? "" : " ") << r[i] + 1;
    }
    cout << endl;
}
