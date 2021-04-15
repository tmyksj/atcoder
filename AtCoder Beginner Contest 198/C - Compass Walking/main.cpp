#include <cmath>
#include <iostream>

using namespace std;

int main() {
    double r, x, y;
    cin >> r >> x >> y;

    double d = sqrt(x * x + y * y);

    if (d == r) {
        cout << "1" << endl;
    } else if (d <= 2 * r) {
        cout << "2" << endl;
    } else {
        cout << ceil(d / r) << endl;
    }
}
