#include <iostream>

using namespace std;

int main() {
    long long a, v, b, w, t;
    cin >> a >> v >> b >> w >> t;
    cout << ((a <= b && a + v * t >= b + w * t) || (a > b && a - v * t <= b - w * t) ? "YES" : "NO") << endl;
}
