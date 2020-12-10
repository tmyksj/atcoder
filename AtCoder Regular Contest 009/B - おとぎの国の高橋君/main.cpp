#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<int> b(10);
    for (int i = 0; i < 10; i++) {
        cin >> b[i];
    }

    int n;
    cin >> n;

    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    map<int, int> m;
    for (int i = 0; i < 10; i++) {
        m[b[i] + '0'] = i;
    }

    vector<pair<int, string>> res(n, make_pair(0, ""));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < static_cast<int>(a[i].size()); j++) {
            res[i].first = 10 * res[i].first + m[a[i][j]];
        }

        res[i].second = a[i];
    }

    sort(res.begin(), res.end());

    for (int i = 0; i < n; i++) {
        cout << res[i].second << endl;
    }
}
