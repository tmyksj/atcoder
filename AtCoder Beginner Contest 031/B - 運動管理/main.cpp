#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int l, h, n;
    cin >> l >> h >> n;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cout << min(max(l - a, 0), max(h - a, -1)) << endl;
    }
}
