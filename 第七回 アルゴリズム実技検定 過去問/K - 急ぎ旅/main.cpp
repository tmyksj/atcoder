#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> u(m), v(m);
    vector<long long> t(m);
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> t[i];
    }

    vector<vector<tuple<int, long long>>> g(n, vector<tuple<int, long long>>(0));
    for (int i = 0; i < m; i++) {
        g[u[i] - 1].push_back(make_tuple(v[i] - 1, t[i]));
        g[v[i] - 1].push_back(make_tuple(u[i] - 1, t[i]));
    }

    long long inf = 1LL << 61;

    vector<tuple<long long, long long>> d(n, make_tuple(inf, 0));
    d[0] = make_tuple(0, a[0]);

    auto que_cmp = [](const tuple<long long, long long, int>& a, const tuple<long long, long long, int>& b) {
        return get<0>(a) != get<1>(b) ? get<0>(a) > get<0>(b) : get<1>(a) < get<1>(b);
    };

    priority_queue<tuple<long long, long long, int>,
            vector<tuple<long long, long long, int>>,
            decltype(que_cmp)> que { que_cmp };
    que.push(make_tuple(0, a[0], 0));
    while (!que.empty()) {
        tuple<long long, long long, int> q = que.top();
        que.pop();

        int p = get<2>(q);
        for (int i = 0; i < static_cast<int>(g[p].size()); i++) {
            int g0 = get<0>(g[p][i]);
            long long g1 = get<1>(g[p][i]);

            if (get<0>(d[g0]) > get<0>(d[p]) + g1
                    || (get<0>(d[g0]) == get<0>(d[p]) + g1 && get<1>(d[g0]) < get<1>(d[p]) + a[g0])) {
                d[g0] = make_tuple(get<0>(d[p]) + g1, get<1>(d[p]) + a[g0]);
                que.push(make_tuple(get<0>(d[p]) + g1, get<1>(d[p]) + a[g0], g0));
            }
        }
    }

    cout << get<1>(d[n - 1]) << endl;
}
