#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    double n;
    cin >> n;
    cout << setprecision(12) << fixed << 9 * n / 5 + 32 << endl;
}
