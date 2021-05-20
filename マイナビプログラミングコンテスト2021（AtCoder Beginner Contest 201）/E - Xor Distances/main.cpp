#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

void dfs(int n, vector<vector<tuple<int, long long>>>& g, vector<long long>& d, int i, int j) {
    for (int k = 0; k < static_cast<int>(g[j].size()); k++) {
        if (get<0>(g[j][k]) != i) {
            d[get<0>(g[j][k])] = d[j] ^ get<1>(g[j][k]);
            dfs(n, g, d, j, get<0>(g[j][k]));
        }
    }
}

int main() {
    int m = 60;
    long long mod = 1000000007;

    int n;
    cin >> n;

    vector<int> u(n - 1), v(n - 1);
    vector<long long> w(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> u[i] >> v[i] >> w[i];
    }

    vector<vector<tuple<int, long long>>> g(n, vector<tuple<int, long long>>(0));
    for (int i = 0; i < n - 1; i++) {
        g[u[i] - 1].push_back(make_tuple(v[i] - 1, w[i]));
        g[v[i] - 1].push_back(make_tuple(u[i] - 1, w[i]));
    }

    vector<long long> d(n, 0);
    dfs(n, g, d, 0, 0);

    vector<vector<long long>> s(n, vector<long long>(m, 0)), t(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            s[i][j] = (i == 0 ? 0 : s[i - 1][j]) + ((d[i] & (1LL << j)) == 0 ? 1 : 0);
            t[i][j] = (i == 0 ? 0 : t[i - 1][j]) + ((d[i] & (1LL << j)) == 0 ? 0 : 1);
        }
    }

    long long res = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if ((d[i] & (1LL << j)) == 0) {
                res = (res + (1LL << j) % mod * (t[n - 1][j] - t[i][j]) % mod) % mod;
            } else {
                res = (res + (1LL << j) % mod * (s[n - 1][j] - s[i][j]) % mod) % mod;
            }
        }
    }

    cout << res << endl;
}
