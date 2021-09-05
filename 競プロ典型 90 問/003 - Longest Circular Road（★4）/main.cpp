#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n - 1), b(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i] >> b[i];
    }

    vector<vector<int>> g(n, vector<int>(0));
    for (int i = 0; i < n - 1; i++) {
        g[a[i] - 1].push_back(b[i] - 1);
        g[b[i] - 1].push_back(a[i] - 1);
    }

    int inf = 1 << 29;

    vector<int> d(n, inf);
    d[0] = 0;

    priority_queue<tuple<int, int>,
            vector<tuple<int, int>>,
            greater<tuple<int, int>>> que;
    que.push(make_tuple(0, 0));
    while (!que.empty()) {
        tuple<int, int> q = que.top();
        que.pop();

        for (int i = 0; i < static_cast<int>(g[get<1>(q)].size()); i++) {
            if (d[g[get<1>(q)][i]] > d[get<1>(q)] + 1) {
                d[g[get<1>(q)][i]] = d[get<1>(q)] + 1;
                que.push(make_tuple(d[g[get<1>(q)][i]], g[get<1>(q)][i]));
            }
        }
    }

    int s = 0;
    for (int i = 1; i < n; i++) {
        if (d[s] < d[i]) {
            s = i;
        }
    }

    fill(d.begin(), d.end(), inf);
    d[s] = 0;

    que.push(make_tuple(0, s));
    while (!que.empty()) {
        tuple<int, int> q = que.top();
        que.pop();

        for (int i = 0; i < static_cast<int>(g[get<1>(q)].size()); i++) {
            if (d[g[get<1>(q)][i]] > d[get<1>(q)] + 1) {
                d[g[get<1>(q)][i]] = d[get<1>(q)] + 1;
                que.push(make_tuple(d[g[get<1>(q)][i]], g[get<1>(q)][i]));
            }
        }
    }

    cout << *max_element(d.begin(), d.end()) + 1 << endl;
}
