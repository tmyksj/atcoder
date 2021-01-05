#include <algorithm>
#include <iostream>

using namespace std;

int dfs(long long n, int p, int q, int r) {
    if (n == 0) {
        return p > q && r % 3 == 0 ? q : 100;
    } else {
        return min(dfs(n / 10, p + 1, q, r + n % 10), dfs(n / 10, p + 1, q + 1, r));
    }
}

int main() {
    long long n;
    cin >> n;

    int res = dfs(n, 0, 0, 0);
    if (res < 100) {
        cout << res << endl;
    } else {
        cout << "-1" << endl;
    }
}
