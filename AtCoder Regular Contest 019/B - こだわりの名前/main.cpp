#include <iostream>
#include <string>

using namespace std;

int main() {
    string a;
    cin >> a;

    int n = a.size();

    int d = 0;
    for (int i = 0; i < n / 2 + n % 2; i++) {
        if (a[i] != a[n - i - 1]) {
            d++;
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (d >= 2 || (d == 1 && a[i] == a[n - i - 1]) || (d == 0 && i != n - i - 1)) {
            res += 25;
        } else if (d == 1 && a[i] != a[n - i - 1]) {
            res += 24;
        }
    }

    cout << res << endl;
}
