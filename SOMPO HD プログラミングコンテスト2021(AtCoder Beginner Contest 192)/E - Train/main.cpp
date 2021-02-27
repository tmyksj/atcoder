#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;

    vector<int> a(m), b(m), t(m), k(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> t[i] >> k[i];
    }

    long long inf = 1LL << 61;

    vector<vector<tuple<int, long long, long long>>> g(n, vector<tuple<int, long long, long long>>(0));
    for (int i = 0; i < m; i++) {
        g[a[i] - 1].push_back(make_tuple(b[i] - 1, t[i], k[i]));
        g[b[i] - 1].push_back(make_tuple(a[i] - 1, t[i], k[i]));
    }

    vector<long long> d(n, inf);
    d[x - 1] = 0;

    priority_queue<tuple<long long, int>,
            vector<tuple<long long, int>>,
            greater<tuple<long long, int>>> que;
    que.push(make_tuple(0, x - 1));
    while (!que.empty()) {
        tuple<long long, int> q = que.top();
        que.pop();

        if (get<0>(q) > d[get<1>(q)]) {
            continue;
        }

        for (int i = 0; i < static_cast<int>(g[get<1>(q)].size()); i++) {
            if (d[get<0>(g[get<1>(q)][i])] > d[get<1>(q)] + get<1>(g[get<1>(q)][i])
                    + (get<2>(g[get<1>(q)][i]) - d[get<1>(q)] % get<2>(g[get<1>(q)][i])) % get<2>(g[get<1>(q)][i])) {
                d[get<0>(g[get<1>(q)][i])] = d[get<1>(q)] + get<1>(g[get<1>(q)][i])
                        + (get<2>(g[get<1>(q)][i]) - d[get<1>(q)] % get<2>(g[get<1>(q)][i])) % get<2>(g[get<1>(q)][i]);
                que.push(make_tuple(d[get<0>(g[get<1>(q)][i])], get<0>(g[get<1>(q)][i])));
            }
        }
    }

    cout << (d[y - 1] < inf ? d[y - 1] : -1) << endl;
}
