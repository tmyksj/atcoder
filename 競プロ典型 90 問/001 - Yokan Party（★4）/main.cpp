#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, l, k;
    cin >> n >> l >> k;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> b(n + 1);
    b[0] = a[0];
    b[n] = l - a[n - 1];
    for (int i = 1; i < n; i++) {
        b[i] = a[i] - a[i - 1];
    }

    long long left = 0, right = l;
    while (right - left > 1) {
        long long mid = (left + right) / 2;

        int c = 0;
        long long s = 0;
        for (int i = 0; i <= n; i++) {
            s += b[i];
            if (s >= mid) {
                c++;
                s = 0;
            }
        }

        if (c - 1 >= k) {
            left = mid;
        } else {
            right = mid;
        }
    }

    cout << left << endl;
}
