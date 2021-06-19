#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < m; i++) {
        g[a[i] - 1].push_back(b[i] - 1);
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        vector<bool> v(n, true);
        v[i] = false;

        queue<int> que;
        que.push(i);
        while (!que.empty()) {
            int q = que.front();
            que.pop();
            res++;

            for (int j = 0; j < static_cast<int>(g[q].size()); j++) {
                if (v[g[q][j]]) {
                    v[g[q][j]] = false;
                    que.push(g[q][j]);
                }
            }
        }
    }

    cout << res << endl;
}
