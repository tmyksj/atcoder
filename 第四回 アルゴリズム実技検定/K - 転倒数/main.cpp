#include <iostream>
#include <vector>

using namespace std;

int main() {
    int a_max = 20;
    long long mod = 1000000000;

    int k;
    cin >> k;

    vector<int> n(k);
    vector<vector<int>> a(k, vector<int>(0));
    for (int i = 0; i < k; i++) {
        cin >> n[i];

        a[i].resize(n[i]);
        for (int j = 0; j < n[i]; j++) {
            cin >> a[i][j];
        }
    }

    int q;
    cin >> q;

    vector<int> b(q);
    for (int i = 0; i < q; i++) {
        cin >> b[i];
    }

    vector<vector<long long>> c(k, vector<long long>(a_max + 1, 0));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n[i]; j++) {
            c[i][a[i][j]]++;
        }
    }

    vector<long long> d(k, 0);
    for (int i = 0; i < k; i++) {
        vector<long long> v(a_max + 1, 0);
        for (int j = 0; j < n[i]; j++) {
            v[a[i][j]]++;
            for (int l = a[i][j] + 1; l <= a_max; l++) {
                d[i] = (d[i] + v[l]) % mod;
            }
        }
    }

    vector<long long> e(a_max + 1, 0);
    long long res = 0;

    for (int i = 0; i < q; i++) {
        for (int j = 0; j <= a_max; j++) {
            for (int l = j + 1; l <= a_max; l++) {
                res = (res + c[b[i] - 1][j] * e[l]) % mod;
            }
        }
        res = (res + d[b[i] - 1]) % mod;

        for (int j = 0; j <= a_max; j++) {
            e[j] = (e[j] + c[b[i] - 1][j]) % mod;
        }
    }

    cout << res << endl;
}
