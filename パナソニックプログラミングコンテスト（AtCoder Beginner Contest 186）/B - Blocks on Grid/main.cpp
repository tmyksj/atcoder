#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int h, w;
    cin >> h >> w;

    vector<int> a(h * w);
    for (int i = 0; i < h * w; i++) {
        cin >> a[i];
    }

    int res = 0;
    for (int i = 0, j = *min_element(a.begin(), a.end()); i < h * w; i++) {
        res += a[i] - j;
    }

    cout << res << endl;
}
