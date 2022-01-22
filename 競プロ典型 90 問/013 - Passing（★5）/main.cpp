#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m), b(m);
    vector<long long> c(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    vector<vector<tuple<int, long long>>> g(n, vector<tuple<int, long long>>(0));
    for (int i = 0; i < m; i++) {
        g[a[i] - 1].push_back(make_tuple(b[i] - 1, c[i]));
        g[b[i] - 1].push_back(make_tuple(a[i] - 1, c[i]));
    }

    long long inf = 1LL << 61;

    vector<long long> d_a(n, inf);
    d_a[0] = 0;

    priority_queue<tuple<long long, int>,
            vector<tuple<long long, int>>,
            greater<tuple<long long, int>>> que_a;
    que_a.push(make_tuple(0, 0));
    while (!que_a.empty()) {
        tuple<long long, int> q = que_a.top();
        que_a.pop();

        for (int i = 0; i < static_cast<int>(g[get<1>(q)].size()); i++) {
            if (d_a[get<0>(g[get<1>(q)][i])] > d_a[get<1>(q)] + get<1>(g[get<1>(q)][i])) {
                d_a[get<0>(g[get<1>(q)][i])] = d_a[get<1>(q)] + get<1>(g[get<1>(q)][i]);
                que_a.push(make_tuple(d_a[get<0>(g[get<1>(q)][i])], get<0>(g[get<1>(q)][i])));
            }
        }
    }

    vector<long long> d_b(n, inf);
    d_b[n - 1] = 0;

    priority_queue<tuple<long long, int>,
            vector<tuple<long long, int>>,
            greater<tuple<long long, int>>> que_b;
    que_b.push(make_tuple(0, n - 1));
    while (!que_b.empty()) {
        tuple<long long, int> q = que_b.top();
        que_b.pop();

        for (int i = 0; i < static_cast<int>(g[get<1>(q)].size()); i++) {
            if (d_b[get<0>(g[get<1>(q)][i])] > d_b[get<1>(q)] + get<1>(g[get<1>(q)][i])) {
                d_b[get<0>(g[get<1>(q)][i])] = d_b[get<1>(q)] + get<1>(g[get<1>(q)][i]);
                que_b.push(make_tuple(d_b[get<0>(g[get<1>(q)][i])], get<0>(g[get<1>(q)][i])));
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << d_a[i] + d_b[i] << endl;
    }
}
