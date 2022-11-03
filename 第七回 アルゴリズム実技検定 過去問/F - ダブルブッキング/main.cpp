#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> d(n), s(n), t(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i] >> s[i] >> t[i];
    }

    vector<int> v(24 * *max_element(d.begin(), d.end()), 0);
    for (int i = 0; i < n; i++) {
        v[24 * (d[i] - 1) + s[i]]++;
        v[24 * (d[i] - 1) + t[i]]--;
    }

    for (int i = 1; i < static_cast<int>(v.size()); i++) {
        v[i] += v[i - 1];
    }

    cout << (*max_element(v.begin(), v.end()) > 1 ? "Yes" : "No") << endl;
}
