#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }

    long long mod = 1000000007;

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < m; i++) {
        g[a[i] - 1].push_back(b[i] - 1);
        g[b[i] - 1].push_back(a[i] - 1);
    }

    vector<long long> d(n, 1 << 29);
    vector<long long> c(n, 0);
    c[0] = 1;

    priority_queue<tuple<int, int>,
            vector<tuple<int, int>>,
            greater<tuple<int, int>>> que;
    que.push(make_tuple(0, 0));
    while (!que.empty()) {
        tuple<int, int> q = que.top();
        que.pop();

        for (int i = 0; i < static_cast<int>(g[get<1>(q)].size()); i++) {
            if (d[g[get<1>(q)][i]] > get<0>(q) + 1) {
                d[g[get<1>(q)][i]] = get<0>(q) + 1;
                c[g[get<1>(q)][i]] = c[get<1>(q)];
                que.push(make_tuple(d[g[get<1>(q)][i]], g[get<1>(q)][i]));
            } else if (d[g[get<1>(q)][i]] == get<0>(q) + 1) {
                c[g[get<1>(q)][i]] = (c[g[get<1>(q)][i]] + c[get<1>(q)]) % mod;
            }
        }
    }

    cout << c[n - 1] << endl;
}
