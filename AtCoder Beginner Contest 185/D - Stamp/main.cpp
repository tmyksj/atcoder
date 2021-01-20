#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    a.push_back(0);
    a.push_back(n + 1);
    sort(a.begin(), a.end());

    int k = n;
    for (int i = 1; i <= m + 1; i++) {
        if (a[i] - a[i - 1] > 1) {
            k = min(k, a[i] - a[i - 1] - 1);
        }
    }

    int res = 0;
    for (int i = 1; i <= m + 1; i++) {
        res += (a[i] - a[i - 1] + k - 2) / k;
    }

    cout << res << endl;
}
