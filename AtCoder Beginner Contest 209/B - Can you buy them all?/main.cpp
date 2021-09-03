#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << (accumulate(a.begin(), a.end(), 0) - n / 2 <= x ? "Yes" : "No") << endl;
}
