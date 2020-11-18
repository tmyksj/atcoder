#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, c;
    cin >> n >> c;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int res = 1 << 29;
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if (i != j) {
                int r = 0;
                for (int k = 0; k < n; k++) {
                    if ((k % 2 == 0 && a[k] != i) || (k % 2 != 0 && a[k] != j)) {
                        r++;
                    }
                }

                res = min(res, c * r);
            }
        }
    }

    cout << res << endl;
}
