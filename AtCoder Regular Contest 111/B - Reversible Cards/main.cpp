#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class union_find {
    vector<int> p;
    vector<int> r;
    vector<int> s;

public:
    union_find(int n) {
        p = vector<int>(n);
        r = vector<int>(n);
        s = vector<int>(n);

        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 0;
            s[i] = 1;
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
            s[ra] = s[rb] = s[ra] + s[rb];
        } else {
            p[rb] = ra;
            s[ra] = s[rb] = s[ra] + s[rb];

            if (r[ra] == r[rb]) {
                r[ra]++;
            }
        }
    }

    int size(int a) {
        s[a] = s[root(a)];
        return s[a];
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    int m = max(*max_element(a.begin(), a.end()), *max_element(b.begin(), b.end()));

    union_find uf(m + 1);
    for (int i = 0; i < n; i++) {
        uf.unite(a[i], b[i]);
    }

    vector<int> c(m + 1, 0);
    for (int i = 0; i < n; i++) {
        c[uf.root(a[i])]++;
    }

    int res = 0;
    for (int i = 0; i <= m; i++) {
        res += min(uf.size(i), c[i]);
    }

    cout << res << endl;
}
