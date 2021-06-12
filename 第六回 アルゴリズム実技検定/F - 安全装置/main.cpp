#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, l, t, x;
    cin >> n >> l >> t >> x;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    int res = 0;
    for (int i = 0, j = 0; i < n; i++) {
        if (a[i] > t && b[i] >= l) {
            res = -1;
            break;
        }

        if (a[i] + j > t && b[i] >= l) {
            res += t - j + x;
            j = 0;
        }

        if (a[i] + j == t && b[i] >= l) {
            res += a[i] + x;
            j = 0;
        } else if (a[i] + j < t && b[i] >= l) {
            res += a[i];
            j += a[i];
        }

        if (b[i] < l) {
            res += a[i];
            j = 0;
        }
    }

    if (res == -1) {
        cout << "forever" << endl;
    } else {
        cout << res << endl;
    }
}
