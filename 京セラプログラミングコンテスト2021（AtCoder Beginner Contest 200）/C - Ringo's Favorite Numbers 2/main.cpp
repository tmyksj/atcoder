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

    long long res = 0;

    vector<int> b(200, 0);
    for (int i = 0; i < n; i++) {
        res += b[a[i] % 200];
        b[a[i] % 200]++;
    }

    cout << res << endl;
}
