#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int res = 0;
    for (int i = 0, j = -1; i < n; i++) {
        if (i - j >= k) {
            res++;
        }
        if (a[i] >= a[i + 1]) {
            j = i;
        }
    }

    cout << res << endl;
}
