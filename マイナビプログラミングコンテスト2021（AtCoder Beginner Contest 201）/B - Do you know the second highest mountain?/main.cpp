#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> s(n);
    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i];
    }

    vector<tuple<int, string>> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = make_tuple(t[i], s[i]);
    }

    sort(v.begin(), v.end());

    cout << get<1>(v[n - 2]) << endl;
}
