#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int res = 1000000000;
    for (int i = -100, r = 0; i <= 100; i++, r = 0) {
        for (int j = 0; j < n; j++) {
            r += (i - a[j]) * (i - a[j]);
        }

        res = min(res, r);
    }

    cout << res << endl;
}
