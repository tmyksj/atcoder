#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class union_find {
    vector<int> p;
    vector<int> r;

public:
    union_find(int n) {
        p = vector<int>(n);
        r = vector<int>(n);

        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 0;
        }
    }

    int root(int a) {
        if (p[a] != a) {
            p[a] = root(p[a]);
        }

        return p[a];
    }

    void unite(int a, int b) {
        int ra = root(a);
        int rb = root(b);

        if (ra == rb) {
            return;
        }

        if (r[ra] < r[rb]) {
            p[ra] = rb;
        } else {
            p[rb] = ra;

            if (r[ra] == r[rb]) {
                r[ra]++;
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<int> c(m), d(m);
    for (int i = 0; i < m; i++) {
        cin >> c[i] >> d[i];
    }

    union_find uf(n);
    for (int i = 0; i < m; i++) {
        uf.unite(c[i] - 1, d[i] - 1);
    }

    vector<long long> s(n, 0);
    for (int i = 0; i < n; i++) {
        s[uf.root(i)] += a[i];
        s[uf.root(i)] -= b[i];
    }

    bool res = *min_element(s.begin(), s.end()) == 0 && *max_element(s.begin(), s.end()) == 0;

    cout << (res ? "Yes" : "No") << endl;
}
