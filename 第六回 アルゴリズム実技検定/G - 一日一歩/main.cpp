#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> a(m), b(m), c(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    vector<int> x(q);
    for (int i = 0; i < q; i++) {
        cin >> x[i];
    }

    vector<vector<tuple<int, long long>>> g(n, vector<tuple<int, long long>>(0));
    for (int i = 0; i < m; i++) {
        g[a[i] - 1].push_back(make_tuple(b[i] - 1, c[i]));
        g[b[i] - 1].push_back(make_tuple(a[i] - 1, c[i]));
    }

    int res = 1;

    vector<bool> v(n, false);
    v[0] = true;

    priority_queue<tuple<long long, int>,
            vector<tuple<long long, int>>,
            greater<tuple<long long, int>>> que;
    for (int i = 0; i < static_cast<int>(g[0].size()); i++) {
        que.push(make_tuple(get<1>(g[0][i]), get<0>(g[0][i])));
    }

    for (int i = 0; i < q; i++) {
        vector<int> w(0);
        while (!que.empty()) {
            tuple<long long, int> q = que.top();

            if (get<0>(q) > x[i]) {
                break;
            }

            que.pop();

            if (v[get<1>(q)]) {
                continue;
            }

            res++;
            v[get<1>(q)] = true;
            w.push_back(get<1>(q));
        }

        for (int j = 0; j < static_cast<int>(w.size()); j++) {
            for (int k = 0; k < static_cast<int>(g[w[j]].size()); k++) {
                if (!v[get<0>(g[w[j]][k])]) {
                    que.push(make_tuple(get<1>(g[w[j]][k]), get<0>(g[w[j]][k])));
                }
            }
        }

        cout << res << endl;
    }
}
