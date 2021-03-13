#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int solve(int n, vector<int>& a) {
    int a_max = *max_element(a.begin(), a.end());
    int a_min = *min_element(a.begin(), a.end());

    if (a_max == a_min) {
        return a_max;
    }

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        if (a[i] == a_min) {
            b[i] = a[i];
        } else {
            b[i] = (a[i] - 1) % a_min + 1;
        }
    }

    return solve(n, b);
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << solve(n, a) << endl;
}
