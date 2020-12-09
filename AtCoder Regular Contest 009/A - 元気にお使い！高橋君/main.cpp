#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int res = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        res += a * b;
    }

    res += 5 * res / 100;

    cout << res << endl;
}
