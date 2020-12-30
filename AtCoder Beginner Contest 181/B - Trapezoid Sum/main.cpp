#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long res = 0;
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        res += b * (b + 1) / 2 - a * (a - 1) / 2;
    }

    cout << res << endl;
}
