#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n = 3;

    vector<tuple<int, int>> v(n, make_tuple(0, 0));
    for (int i = 0; i < n; i++) {
        cin >> get<0>(v[i]);
        get<1>(v[i]) = i;
    }

    sort(v.begin(), v.end());

    cout << static_cast<char>(get<1>(v[1]) + 'A') << endl;
}
