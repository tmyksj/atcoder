#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool dfs(const vector<vector<int>>& g, vector<int>& a, int p) {
    if (a[p] == -1) {
        return true;
    }

    if (a[p] == 0) {
        a[p] = -1;

        for (int i = 0; i < static_cast<int>(g[p].size()); i++) {
            if (dfs(g, a, g[p][i])) {
                return true;
            }
        }

        a[p] = 1;
    }

    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> u(m), v(m);
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i];
    }

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < m; i++) {
        g[u[i] - 1].push_back(v[i] - 1);
    }

    bool res = false;

    vector<int> a(n, 0);
    for (int i = 0; i < n; i++) {
        res = res || (a[i] == 0 && dfs(g, a, i));
    }

    cout << (res ? "Yes" : "No") << endl;
}
