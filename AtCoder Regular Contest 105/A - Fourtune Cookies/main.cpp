#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 4;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    bool res = false;
    for (int i = 0; i < (1 << n); i++) {
        int s = 0, t = 0;
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) == 0) {
                s += a[j];
            } else {
                t += a[j];
            }
        }

        res = res || s == t;
    }

    cout << (res ? "Yes" : "No") << endl;
}
