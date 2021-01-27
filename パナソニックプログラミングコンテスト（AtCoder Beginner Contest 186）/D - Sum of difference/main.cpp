#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    long long res = 0, sum = accumulate(a.begin(), a.end(), 0LL);
    for (int i = 0; i < n; i++) {
        res += sum - (n - i) * a[i];
        sum -= a[i];
    }

    cout << res << endl;
}
