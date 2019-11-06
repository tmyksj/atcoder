#include <iostream>

using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;

    if (m - 2 * n >= 0) {
        cout << n + (m - 2 * n) / 4 << endl;
    } else {
        cout << m / 2 << endl;
    }
}
