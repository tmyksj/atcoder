#include <iostream>
#include <map>
#include <utility>
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
            p[a] = this->root(p[a]);
        }

        return p[a];
    }

    void unite(int a, int b) {
        int ra = this->root(a);
        int rb = this->root(b);

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
    int n, k, l;
    cin >> n >> k >> l;

    union_find pq(n);
    for (int i = 0; i < k; i++) {
        int p, q;
        cin >> p >> q;
        pq.unite(p - 1, q - 1);
    }

    union_find rs(n);
    for (int i = 0; i < l; i++) {
        int r, s;
        cin >> r >> s;
        rs.unite(r - 1, s - 1);
    }

    map<pair<int, int>, int> cnt;
    for (int i = 0; i < n; i++) {
        cnt[make_pair(pq.root(i), rs.root(i))]++;
    }

    cout << cnt[make_pair(pq.root(0), rs.root(0))];
    for (int i = 1; i < n; i++) {
        cout << " " << cnt[make_pair(pq.root(i), rs.root(i))];
    }
    cout << endl;
}
