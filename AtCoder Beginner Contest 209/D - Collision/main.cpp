#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n - 1), b(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i] >> b[i];
    }

    vector<int> c(q), d(q);
    for (int i = 0; i < q; i++) {
        cin >> c[i] >> d[i];
    }

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < n - 1; i++) {
        g[a[i] - 1].push_back(b[i] - 1);
        g[b[i] - 1].push_back(a[i] - 1);
    }

    int inf = 1 << 29;

    vector<int> p(n, inf);
    p[0] = 0;

    priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> que;
    que.push(make_tuple(0, 0));
    while (!que.empty()) {
        tuple<int, int> t = que.top();
        que.pop();

        for (int i = 0; i < static_cast<int>(g[get<1>(t)].size()); i++) {
            if (p[g[get<1>(t)][i]] > p[get<1>(t)] + 1) {
                p[g[get<1>(t)][i]] = p[get<1>(t)] + 1;
                que.push(make_tuple(p[g[get<1>(t)][i]], g[get<1>(t)][i]));
            }
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ((p[c[i] - 1] + p[d[i] - 1]) % 2 == 0 ? "Town" : "Road") << endl;
    }
}
