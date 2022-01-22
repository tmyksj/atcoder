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
    int h, w, q;
    cin >> h >> w >> q;

    vector<vector<bool>> v(h, vector<bool>(w, false));
    union_find uf(h * w);

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;

        if (t == 1) {
            int r, c;
            cin >> r >> c;

            v[r - 1][c - 1] = true;

            int dy[] = { -1, 0, 0, 1 };
            int dx[] = { 0, -1, 1, 0 };

            for (int i = 0; i < 4; i++) {
                if (0 <= r + dy[i] - 1 && r + dy[i] - 1 < h
                        && 0 <= c + dx[i] - 1 && c + dx[i] - 1 < w
                        && v[r + dy[i] - 1][c + dx[i] - 1]) {
                    uf.unite(w * (r - 1) + c - 1, w * (r + dy[i] - 1) + c + dx[i] - 1);
                }
            }
        } else {
            int ra, ca, rb, cb;
            cin >> ra >> ca >> rb >> cb;

            if (v[ra - 1][ca - 1] && v[rb - 1][cb - 1]
                    && uf.root(w * (ra - 1) + ca - 1) == uf.root(w * (rb - 1) + cb - 1)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
}
