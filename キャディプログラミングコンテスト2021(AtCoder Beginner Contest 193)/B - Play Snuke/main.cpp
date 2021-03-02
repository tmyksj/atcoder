#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n), p(n), x(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> p[i] >> x[i];
    }

    int res = -1;
    for (int i = 0; i < n; i++) {
        if ((res == -1 || res > p[i]) && x[i] - a[i] > 0) {
            res = p[i];
        }
    }

    cout << res << endl;
}
