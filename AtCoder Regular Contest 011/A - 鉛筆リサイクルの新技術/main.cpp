#include <iostream>

using namespace std;

int main() {
    int m, nl, nu;
    cin >> m >> nl >> nu;

    int res = nu;
    for (int i = nu, j = 0; i + j >= m; ) {
        int v = i, w = j;
        i = (v + w) / m * nl;
        j = (v + w) % m;
        res += i;
    }

    cout << res << endl;
}
