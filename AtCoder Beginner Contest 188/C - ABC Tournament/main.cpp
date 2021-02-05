#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        cin >> a[i];
    }

    vector<pair<int, int>> b(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        b[i] = make_pair(a[i], i);
    }

    cout << min(*max_element(b.begin(), b.begin() + (1 << (n - 1))),
            *max_element(b.begin() + (1 << (n - 1)), b.end())).second + 1 << endl;
}
