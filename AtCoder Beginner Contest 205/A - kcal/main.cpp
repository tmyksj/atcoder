#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << setprecision(12) << fixed << a * b / 100.0 << endl;
}
