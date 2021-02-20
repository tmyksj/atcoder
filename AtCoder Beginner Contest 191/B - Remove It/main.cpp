#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> res(0);
    for (int i = 0; i < n; i++) {
        if (a[i] != x) {
            res.push_back(a[i]);
        }
    }

    for (int i = 0; i < static_cast<int>(res.size()); i++) {
        cout << (i == 0 ? "" : " ") << res[i];
    }
    cout << endl;
}
