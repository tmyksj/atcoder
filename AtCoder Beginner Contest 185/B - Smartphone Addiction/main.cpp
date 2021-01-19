#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, t;
    cin >> n >> m >> t;

    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }

    vector<int> c(1, 0);
    for (int i = 0; i < m; i++) {
        c.push_back(a[i]);
        c.push_back(b[i]);
    }
    c.push_back(t);

    vector<int> d(1, n);
    for (int i = 1; i < static_cast<int>(c.size()); i++) {
        if (i % 2 == 0) {
            d.push_back(min(d[i - 1] - c[i - 1] + c[i], n));
        } else {
            d.push_back(max(d[i - 1] + c[i - 1] - c[i], 0));
        }
    }

    cout << (*min_element(d.begin(), d.end()) > 0 ? "Yes" : "No") << endl;
}
