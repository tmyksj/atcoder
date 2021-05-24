#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

bool comp(tuple<string, string>& a, tuple<string, string>& b) {
    if (get<1>(a).size() != get<1>(b).size()) {
        return get<1>(a).size() < get<1>(b).size();
    } else if (get<1>(a) != get<1>(b)) {
        return get<1>(a) < get<1>(b);
    } else {
        return get<0>(a).size() > get<0>(b).size();
    }
}

int main() {
    int n;
    cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<tuple<string, string>> v(n);
    for (int i = 0; i < n; i++) {
        int p = 0;
        for (; p < static_cast<int>(s[i].size()) && s[i][p] == '0'; p++) {
        }

        v[i] = make_tuple(s[i], s[i].substr(p));
    }

    sort(v.begin(), v.end(), comp);

    for (int i = 0; i < n; i++) {
        cout << get<0>(v[i]) << endl;
    }
}
