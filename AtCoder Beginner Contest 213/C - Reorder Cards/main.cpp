#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    int h, w, n;
    cin >> h >> w >> n;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    vector<int> c(a), d(b);

    sort(c.begin(), c.end());
    sort(d.begin(), d.end());

    c.erase(unique(c.begin(), c.end()), c.end());
    d.erase(unique(d.begin(), d.end()), d.end());

    for (int i = 0; i < n; i++) {
        cout << distance(c.begin(), lower_bound(c.begin(), c.end(), a[i])) + 1 << " "
                << distance(d.begin(), lower_bound(d.begin(), d.end(), b[i])) + 1 << endl;
    }
}
