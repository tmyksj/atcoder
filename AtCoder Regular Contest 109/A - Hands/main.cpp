#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int a, b, x, y;
    cin >> a >> b >> x >> y;

    if (a <= b) {
        cout << x + (b - a) * min(2 * x, y) << endl;
    } else {
        cout << x + (a - b - 1) * min(2 * x, y) << endl;
    }
}
