#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    double a, b;
    cin >> a >> b;
    cout << setprecision(12) << fixed << 100 * (a - b) / a << endl;
}
