#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> t(n), l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> l[i] >> r[i];
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            bool r0 = (t[i] == 1 || t[i] == 2) && (t[j] == 1 || t[j] == 3) && l[i] <= r[j];
            bool r1 = (t[i] == 3 || t[i] == 4 || t[j] == 2 || t[j] == 4) && l[i] < r[j];
            bool r2 = (t[j] == 1 || t[j] == 2) && (t[i] == 1 || t[i] == 3) && l[j] <= r[i];
            bool r3 = (t[j] == 3 || t[j] == 4 || t[i] == 2 || t[i] == 4) && l[j] < r[i];
            if ((r0 || r1) && (r2 || r3)) {
                res++;
            }
        }
    }

    cout << res << endl;
}
