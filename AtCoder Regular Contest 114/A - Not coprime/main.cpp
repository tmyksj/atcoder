#include <iostream>
#include <vector>

using namespace std;

template <class T>
T gcm(T a, T b) {
    if (a < b) {
        T w = a;
        a = b;
        b = w;
    }

    while (b != 0) {
        T w = a % b;
        a = b;
        b = w;
    }

    return a;
}

int main() {
    vector<long long> p = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };

    int n;
    cin >> n;

    vector<long long> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    long long res = 1;
    for (int i = 0; i < static_cast<int>(p.size()); i++) {
        res *= p[i];
    }

    for (int i = 1; i < (1 << p.size()); i++) {
        long long q = 1;
        for (int j = 0; j < static_cast<int>(p.size()); j++) {
            if ((i & (1 << j)) > 0) {
                q *= p[j];
            }
        }

        bool r = true;
        for (int j = 0; j < n; j++) {
            r = r && gcm(q, x[j]) > 1;
        }

        if (r && res > q) {
            res = q;
        }
    }

    cout << res << endl;
}
