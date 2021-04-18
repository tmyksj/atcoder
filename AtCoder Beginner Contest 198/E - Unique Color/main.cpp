#include <iostream>
#include <map>
#include <vector>

using namespace std;

void solve(int n, vector<int>& c, vector<vector<int>>& g, map<int, int>& m, int i, int p, vector<bool>& r) {
    r[i] = m[c[i]] == 0;

    m[c[i]]++;
    for (int j = 0; j < static_cast<int>(g[i].size()); j++) {
        if (g[i][j] != p) {
            solve(n, c, g, m, g[i][j], i, r);
        }
    }
    m[c[i]]--;
}

int main() {
    int n;
    cin >> n;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    vector<int> a(n - 1), b(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i] >> b[i];
    }

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < n - 1; i++) {
        g[a[i] - 1].push_back(b[i] - 1);
        g[b[i] - 1].push_back(a[i] - 1);
    }

    map<int, int> m;
    vector<bool> res(n, false);
    solve(n, c, g, m, 0, -1, res);

    for (int i = 0; i < n; i++) {
        if (res[i]) {
            cout << i + 1 << endl;
        }
    }
}
