#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int a_max = *max_element(a.begin(), a.end());

    int p = 0, q = 0;
    for (int i = 2; i <= a_max; i++) {
        int r = 0;
        for (int j = 0; j < n; j++) {
            if (a[j] % i == 0) {
                r++;
            }
        }

        if (q < r) {
            p = i;
            q = r;
        }
    }

    cout << p << endl;
}
