#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>

using namespace std;

template <class T, class Container = std::vector<T>, class Compare = less<typename Container::value_type>>
class segment_tree {
    int s;
    Container c;
    Compare comp;

    int init(int n) {
        for (s = 1; s < n; s <<= 1) {
        }

        return n + s - 1;
    }

    typename Container::const_reference get(int n, int m, int i, int j, int k) {
        if (n <= j && k <= m) {
            return *(c.begin() + i);
        } else if (n <= (j + k) / 2 && (j + k + 1) / 2 <= m) {
            typename Container::const_reference a = get(n, m, 2 * i + 1, j, (j + k) / 2);
            typename Container::const_reference b = get(n, m, 2 * i + 2, (j + k + 1) / 2, k);
            return comp(a, b) ? a : b;
        } else if (m <= (j + k) / 2) {
            return get(n, m, 2 * i + 1, j, (j + k) / 2);
        } else {
            return get(n, m, 2 * i + 2, (j + k + 1) / 2, k);
        }
    }

public:
    segment_tree(int n, const Compare& c = Compare()) :
        c(init(n)),
        comp(c) {
    }

    typename Container::const_reference get(int n) {
        return *(c.begin() + n + s - 1);
    }

    typename Container::const_reference get(int n, int m) {
        return get(n, m, 0, 0, s - 1);
    }

    void set(int n, typename Container::const_reference x) {
        int i = n + s - 1;
        *(c.begin() + i) = x;

        while (i > 0) {
            i = (i - 1) / 2;
            *(c.begin() + i) = comp(*(c.begin() + 2 * i + 1), *(c.begin() + 2 * i + 2))
                    ? *(c.begin() + 2 * i + 1) : *(c.begin() + 2 * i + 2);
        }
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    map<int, set<int>> m;
    for (int i = 0; i < n; i++) {
        m[a[i]].insert(i);
    }

    segment_tree<int> seg(n);
    for (int i = 0; i < n; i++) {
        seg.set(i, a[i]);
    }

    for (int i = 0; i < q; i++) {
        int t, x, y;
        cin >> t >> x >> y;

        if (t == 1) {
            int z = seg.get(x - 1);

            m[z].erase(x - 1);
            m[y].insert(x - 1);
            seg.set(x - 1, y);
        } else {
            int z = seg.get(x - 1, y - 1);

            set<int>::iterator i = m[z].lower_bound(x - 1);
            set<int>::iterator j = m[z].upper_bound(y - 1);

            cout << distance(i, j);
            for (; i != j; i++) {
                cout << " " << *i + 1;
            }
            cout << endl;
        }
    }
}
