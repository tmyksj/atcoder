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

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    vector<int> d(n, 0);
    for (int i = 0; i < n; i++) {
        d[b[c[i] - 1] - 1]++;
    }

    long long res = 0;
    for (int i = 0; i < n; i++) {
        res += d[a[i] - 1];
    }

    cout << res << endl;
}
