#include <iostream>

using namespace std;

int main() {
    int a, b, c, k, s, t;
    cin >> a >> b >> c >> k >> s >> t;
    cout << a * s + b * t - c * (k <= s + t ? s + t : 0) << endl;
}
