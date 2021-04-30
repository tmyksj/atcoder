#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    map<string, int> m;
    for (int i = 0; i < n; i++) {
        m[s[i]]++;
    }

    vector<tuple<int, string>> v(0);
    for (map<string, int>::iterator i = m.begin(); i != m.end(); i++) {
        v.push_back(make_tuple(i->second, i->first));
    }

    sort(v.begin(), v.end(), greater<tuple<int, string>>());

    if ((k > 1 && get<0>(v[k - 2]) == get<0>(v[k - 1]))
            || (k < static_cast<int>(v.size()) && get<0>(v[k - 1]) == get<0>(v[k]))) {
        cout << "AMBIGUOUS" << endl;
    } else {
        cout << get<1>(v[k - 1]) << endl;
    }
}
