#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }

    int a = *max_element(d.begin(), d.end());
    int b = accumulate(d.begin(), d.end(), 0);

    cout << b << endl;
    cout << max(2 * a - b, 0) << endl;
}
