#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int n, s;
    cin >> n >> s;

    int res = 0;
    for (int i = 1; i <= n && i < s; i++) {
        res += min(n, s - i);
    }

    cout << res << endl;
}
