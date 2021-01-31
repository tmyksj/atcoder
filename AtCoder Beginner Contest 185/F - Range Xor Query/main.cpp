#include <iostream>
#include <vector>

using namespace std;

template <class T>
class binary_indexed_tree {
    vector<T> a;

    int lsb(int i) {
        return i & -i;
    }

public:
    binary_indexed_tree(int n) {
        a = vector<T>(n, 0);
    }

    void xor_add(int i, T v) {
        for (; i < static_cast<int>(a.size()); i += lsb(i + 1)) {
            a[i] ^= v;
        }
    }

    int xor_sum(int i) {
        T r = 0;
        for (; i >= 0; i -= lsb(i + 1)) {
            r ^= a[i];
        }
        return r;
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> t(q), x(q), y(q);
    for (int i = 0; i < q; i++) {
        cin >> t[i] >> x[i] >> y[i];
    }

    binary_indexed_tree<int> bit(n + 1);
    for (int i = 0; i < n; i++) {
        bit.xor_add(i + 1, a[i]);
    }

    for (int i = 0; i < q; i++) {
        if (t[i] == 1) {
            bit.xor_add(x[i], y[i]);
        } else {
            cout << (bit.xor_sum(x[i] - 1) ^ bit.xor_sum(y[i])) << endl;
        }
    }
}
