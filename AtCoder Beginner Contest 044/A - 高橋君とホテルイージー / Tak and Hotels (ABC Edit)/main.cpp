#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    long long n, k, x, y;
    cin >> n >> k >> x >> y;
    cout << min(n, k) * x + max(0LL, n - k) * y << endl;
}
