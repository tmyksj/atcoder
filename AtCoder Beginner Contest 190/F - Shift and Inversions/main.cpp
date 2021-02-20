#include <iostream>
#include <vector>

using namespace std;

template <class T>
class segment_tree {
    size_t n;
    T a;
    vector<T> v;

    T get(size_t i, size_t j, size_t k, size_t l, size_t m) {
        if (m <= i || j <= l) {
            return a;
        } else if (i <= l && m <= j) {
            return v[k];
        } else {
            return op(get(i, j, 2 * k + 1, l, (l + m) / 2), get(i, j, 2 * k + 2, (l + m) / 2, m));
        }
    }

public:
    segment_tree(size_t n, T a) {
        this->n = 1;
        while (this->n < n) {
            this->n *= 2;
        }

        this->a = a;
        this->v = vector<T>(2 * this->n - 1, this->a);
    }

    T op(T a, T b) {
        return a + b;
    }

    T get(size_t i, size_t j) {
        return get(i, j, 0, 0, n);
    }

    void set(size_t i, T a) {
        i += n - 1;
        v[i] = a;

        while (i > 0) {
            i = (i - 1) / 2;
            v[i] = op(v[2 * i + 1], v[2 * i + 2]);
        }
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long p = 0;
    segment_tree<long long> st(n, 0);
    for (int i = 0; i < n; i++) {
        p += st.get(a[i] + 1, n);
        st.set(a[i], 1);
    }

    vector<long long> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = p;

        p -= st.get(0, a[i]);
        p += st.get(a[i] + 1, n);
    }

    for (int i = 0; i < n; i++) {
        cout << res[i] << endl;
    }
}
