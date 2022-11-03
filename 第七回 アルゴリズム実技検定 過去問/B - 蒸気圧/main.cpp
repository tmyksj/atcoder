#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    cout << setprecision(12) << fixed << static_cast<double>(min(a, b * c)) / b << endl;
}
