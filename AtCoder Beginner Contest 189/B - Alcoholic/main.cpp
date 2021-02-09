#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> v(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i] >> p[i];
    }

    int res = -1;
    for (int i = 0, j = 0; i < n; i++) {
        j += v[i] * p[i];
        if (j > 100 * x) {
            res = i + 1;
            break;
        }
    }

    cout << res << endl;
}
