#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    vector<int> r(q), u(q), v(q);
    for (int i = 0; i < q; i++) {
        cin >> r[i];
        if (r[i] == 1 || r[i] == 2) {
            cin >> v[i];
        } else {
            cin >> u[i] >> v[i];
        }
    }

    long long d = 0;
    vector<long long> g(n);
    map<long long, int> m;
    for (int i = 0; i < n; i++) {
        g[i] = h[i];
        if (i < n - 1) {
            m[(i % 2 == 0 ? 1 : -1) * (h[i + 1] - h[i])]++;
        }
    }

    vector<long long> res(q);
    for (int i = 0; i < q; i++) {
        if (r[i] == 1) {
            d += v[i];
        } else if (r[i] == 2) {
            d -= v[i];
        } else {
            if (u[i] > 1) {
                m[(u[i] % 2 == 0 ? 1 : -1) * (g[u[i] - 1] - g[u[i] - 2])]--;
            }
            if (u[i] < n) {
                m[(u[i] % 2 == 0 ? -1 : 1) * (g[u[i]] - g[u[i] - 1])]--;
            }

            g[u[i] - 1] += v[i];

            if (u[i] > 1) {
                m[(u[i] % 2 == 0 ? 1 : -1) * (g[u[i] - 1] - g[u[i] - 2])]++;
            }
            if (u[i] < n) {
                m[(u[i] % 2 == 0 ? -1 : 1) * (g[u[i]] - g[u[i] - 1])]++;
            }
        }

        res[i] = m[d];
    }

    for (int i = 0; i < q; i++) {
        cout << res[i] << endl;
    }
}
