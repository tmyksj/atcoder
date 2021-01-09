#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    double sx, sy, gx, gy;
    cin >> sx >> sy >> gx >> gy;
    cout << setprecision(12) << fixed << (sx * (gy + sy) + sy * (gx - sx)) / (gy + sy) << endl;
}
