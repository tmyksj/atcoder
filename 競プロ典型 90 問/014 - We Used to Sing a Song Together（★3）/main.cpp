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

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long res = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) {
            res += a[i] - b[i];
        } else {
            res += b[i] - a[i];
        }
    }

    cout << res << endl;
}
