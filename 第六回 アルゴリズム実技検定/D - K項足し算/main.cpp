#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> b(n + 1, 0);
    for (int i = 0; i < n; i++) {
        b[i + 1] = b[i] + a[i];
    }

    for (int i = 0; i < n - k + 1; i++) {
        cout << b[i + k] - b[i] << endl;
    }
}
