#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

vector<vector<long long>> mul(vector<vector<long long>>& a, vector<vector<long long>>& b) {
    vector<vector<long long>> c(a.size(), vector<long long>(b[0].size(), 0));
    for (int i = 0; i < static_cast<int>(a.size()); i++) {
        for (int j = 0; j < static_cast<int>(b[0].size()); j++) {
            for (int k = 0; k < static_cast<int>(a[0].size()); k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

int main() {
    int n;
    cin >> n;

    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    int m;
    cin >> m;

    vector<int> op(m);
    vector<long long> p(m, 0);
    for (int i = 0; i < m; i++) {
        cin >> op[i];
        if (op[i] == 3 || op[i] == 4) {
            cin >> p[i];
        }
    }

    int q;
    cin >> q;

    vector<int> a(q), b(q);
    for (int i = 0; i < q; i++) {
        cin >> a[i] >> b[i];
    }

    vector<tuple<int, int, int>> c(q);
    for (int i = 0; i < q; i++) {
        c[i] = make_tuple(a[i], b[i] - 1, i);
    }

    sort(c.begin(), c.end());

    vector<vector<long long>> r(3, vector<long long>(3, 0));
    r[0][0] = r[1][1] = r[2][2] = 1;

    vector<tuple<long long, long long>> res(q);
    for (int i = 0, j = 0; i < q; i++) {
        for (; j < get<0>(c[i]); j++) {
            if (op[j] == 1) {
                vector<vector<long long>> s(3, vector<long long>(3, 0));
                s[0][1] = 1; s[1][0] = -1; s[2][2] = 1;
                r = mul(s, r);
            } else if (op[j] == 2) {
                vector<vector<long long>> s(3, vector<long long>(3, 0));
                s[0][1] = -1; s[1][0] = 1; s[2][2] = 1;
                r = mul(s, r);
            } else if (op[j] == 3) {
                vector<vector<long long>> s(3, vector<long long>(3, 0)),
                        t(3, vector<long long>(3, 0)), u(3, vector<long long>(3, 0));
                s[0][0] = 1; s[0][2] = -p[j]; s[1][1] = 1; s[2][2] = 1;
                t[0][0] = -1; t[1][1] = 1; t[2][2] = 1;
                u[0][0] = 1; u[0][2] = p[j]; u[1][1] = 1; u[2][2] = 1;
                r = mul(s, r); r = mul(t, r); r = mul(u, r);
            } else {
                vector<vector<long long>> s(3, vector<long long>(3, 0)),
                        t(3, vector<long long>(3, 0)), u(3, vector<long long>(3, 0));
                s[0][0] = 1; s[1][1] = 1; s[1][2] = -p[j]; s[2][2] = 1;
                t[0][0] = 1; t[1][1] = -1; t[2][2] = 1;
                u[0][0] = 1; u[1][1] = 1; u[1][2] = p[j]; u[2][2] = 1;
                r = mul(s, r); r = mul(t, r); r = mul(u, r);
            }
        }

        res[get<2>(c[i])] = make_tuple(r[0][0] * x[get<1>(c[i])] + r[0][1] * y[get<1>(c[i])] + r[0][2],
                r[1][0] * x[get<1>(c[i])] + r[1][1] * y[get<1>(c[i])] + r[1][2]);
    }

    for (int i = 0; i < q; i++) {
        cout << get<0>(res[i]) << " " << get<1>(res[i]) << endl;
    }
}
