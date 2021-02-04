#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    long long res = 0;
    for (int i = 0; i < n; i++) {
        res += a[i] * b[i];
    }

    cout << (res == 0 ? "Yes" : "No") << endl;
}
