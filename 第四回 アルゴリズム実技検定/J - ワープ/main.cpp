#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, m, xab, xac, xbc;
    string s;
    cin >> n >> m >> xab >> xac >> xbc >> s;

    vector<int> a(m), b(m), c(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    vector<vector<tuple<int, long long>>> g(n + 3, vector<tuple<int, long long>>(0));
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            g[i].push_back(make_tuple(n + 1, xab));
            g[i].push_back(make_tuple(n + 2, xac));
            g[n].push_back(make_tuple(i, 0));
        } else if (s[i] == 'B') {
            g[i].push_back(make_tuple(n, xab));
            g[i].push_back(make_tuple(n + 2, xbc));
            g[n + 1].push_back(make_tuple(i, 0));
        } else {
            g[i].push_back(make_tuple(n, xac));
            g[i].push_back(make_tuple(n + 1, xbc));
            g[n + 2].push_back(make_tuple(i, 0));
        }
    }
    for (int i = 0; i < m; i++) {
        g[a[i] - 1].push_back(make_tuple(b[i] - 1, c[i]));
        g[b[i] - 1].push_back(make_tuple(a[i] - 1, c[i]));
    }

    long long inf = 1LL << 61;
    vector<long long> d(n + 3, inf);
    d[0] = 0;

    priority_queue<tuple<long long, int>,
            vector<tuple<long long, int>>,
            greater<tuple<long long, int>>> que;
    que.push(make_tuple(0, 0));
    while (!que.empty()) {
        tuple<long long, int> q = que.top();
        que.pop();

        if (get<1>(q) == n - 1) {
            break;
        }

        if (get<0>(q) > d[get<1>(q)]) {
            continue;
        }

        for (int i = 0; i < static_cast<int>(g[get<1>(q)].size()); i++) {
            if (d[get<0>(g[get<1>(q)][i])] > d[get<1>(q)] + get<1>(g[get<1>(q)][i])) {
                d[get<0>(g[get<1>(q)][i])] = d[get<1>(q)] + get<1>(g[get<1>(q)][i]);
                que.push(make_tuple(d[get<0>(g[get<1>(q)][i])], get<0>(g[get<1>(q)][i])));
            }
        }
    }

    cout << d[n - 1] << endl;
}
