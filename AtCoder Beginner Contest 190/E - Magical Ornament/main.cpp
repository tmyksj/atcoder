#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int dijkstra(int n, vector<vector<int>>& g, int s, int t) {
    int inf = 1 << 29;

    vector<int> d(n, inf);
    d[s] = 0;

    priority_queue<tuple<int, int>,
            vector<tuple<int, int>>,
            greater<tuple<int, int>>> que;
    que.push(make_tuple(0, s));
    while (!que.empty()) {
        tuple<int, int> q = que.top();
        que.pop();

        if (get<1>(q) == t) {
            break;
        }

        for (int i = 0; i < static_cast<int>(g[get<1>(q)].size()); i++) {
            if (d[g[get<1>(q)][i]] > d[get<1>(q)] + 1) {
                d[g[get<1>(q)][i]] = d[get<1>(q)] + 1;
                que.push(make_tuple(d[g[get<1>(q)][i]], g[get<1>(q)][i]));
            }
        }
    }

    return d[t] < inf ? d[t] : -1;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }

    int k;
    cin >> k;

    vector<int> c(k);
    for (int i = 0; i < k; i++) {
        cin >> c[i];
    }

    int inf = 1 << 29;

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < m; i++) {
        g[a[i] - 1].push_back(b[i] - 1);
        g[b[i] - 1].push_back(a[i] - 1);
    }

    vector<vector<int>> h(k, vector<int>(k, inf));
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            int dist = dijkstra(n, g, c[i] - 1, c[j] - 1);
            if (dist >= 0) {
                h[i][j] = dist;
                h[j][i] = dist;
            }
        }
    }

    vector<vector<int>> dp(1 << k, vector<int>(k, inf));
    for (int i = 0; i < k; i++) {
        dp[1 << i][i] = 1;
    }

    for (int i = 1; i < (1 << k); i++) {
        for (int j = 0; j < k; j++) {
            for (int l = 0; l < k; l++) {
                dp[i | (1 << l)][l] = min(dp[i | (1 << l)][l], dp[i][j] + h[j][l]);
            }
        }
    }

    int res = inf;
    for (int i = 0; i < k; i++) {
        res = min(res, dp[(1 << k) - 1][i]);
    }

    cout << (res < inf ? res : -1) << endl;
}
