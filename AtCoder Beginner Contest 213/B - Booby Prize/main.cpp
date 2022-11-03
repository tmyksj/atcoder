#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<tuple<int, int>> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = make_tuple(a[i], i);
    }

    sort(b.begin(), b.end());

    cout << get<1>(b[n - 2]) + 1 << endl;
}
