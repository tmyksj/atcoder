#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<bool> d(10, false);
    for (int i = 0; i < k; i++) {
        int di;
        cin >> di;
        d[di] = true;
    }

    int res = n;
    for (; ; res++) {
        bool valid = true;
        for (int i = res; i > 0; i /= 10) {
            valid = (valid && !d[i % 10]);
        }

        if (valid) {
            break;
        }
    }

    cout << res << endl;
}
