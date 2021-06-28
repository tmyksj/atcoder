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
    int a_max = 200000;

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    union_find uf(a_max + 1);
    for (int i = 0; i < n / 2; i++) {
        uf.unite(a[i], a[n - i - 1]);
    }

    int res = 0;
    for (int i = 0; i <= a_max; i++) {
        if (uf.root(i) == i) {
            res += uf.size(i) - 1;
        }
    }

    cout << res << endl;
}
