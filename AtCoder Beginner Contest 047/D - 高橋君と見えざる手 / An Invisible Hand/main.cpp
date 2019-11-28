#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, t;
    cin >> n >> t;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int a_max = -1, a_diff_max = -1, res = 0;
    for (int i = n - 1; i >= 0; i--) {
        a_max = max(a_max, a[i]);

        if (a_diff_max < a_max - a[i]) {
            a_diff_max = a_max - a[i];
            res = 1;
        } else if (a_diff_max == a_max - a[i]) {
            res++;
        }
    }

    cout << res << endl;
}
